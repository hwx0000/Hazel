#include "hzpch.h"
#include "Hazel/Utils/Utils.h"
#include "mono/metadata/assembly.h"
#include "mono/metadata/image.h"
#include "Scripting.h"
#include "mono/jit/jit.h"

namespace Hazel
{
    // 读取一个C# dll到Mono里, 然后返回对应的Assembly指针
    MonoAssembly* Scripting::LoadCSharpAssembly(const std::string& assemblyPath)
    {
		// InitMono部分
		// Let Mono know where the .NET libraries are located.
		mono_set_assemblies_path("mono/lib");
		//mono_set_assemblies_path("../Hazel/vendor/Mono/DotNetLibs/4.5");
		//mono_set_assemblies_path("C:/GitRepository/Hazel/Hazel/Hazel/vendor/Mono/DotNetLibs");
	

		MonoDomain* rootDomain = mono_jit_init("MyScriptRuntime");
		if (rootDomain == nullptr)
		{
			// Maybe log some error here
			return nullptr;
		}

		// Store the root domain pointer
		//s_RootDomain = rootDomain;

		// Create an App Domain
		auto s_AppDomain = mono_domain_create_appdomain("MyAppDomain", nullptr);
		mono_domain_set(s_AppDomain, true);


        uint32_t fileSize = 0;
        // 用于直接读取C#的.dll文件, 把它读作bytes数组
        char* fileData = Utils::ReadBytes(assemblyPath, &fileSize);

        // NOTE: We can't use this image for anything other than loading the assembly because this image doesn't have a reference to the assembly
        MonoImageOpenStatus status;
        // 把读取的dll传给Mono, 得到的assembly会存在Mono这边, 暂时不需要反射
        MonoImage* image = mono_image_open_from_data_full(fileData, fileSize, true, &status, false);

        if (status != MONO_IMAGE_OK)
        {
            const char* errorMessage = mono_image_strerror(status);
            // Log some error message using the errorMessage data
            return nullptr;
        }

        // 从image里读取assembly指针
        MonoAssembly* assembly = mono_assembly_load_from_full(image, assemblyPath.c_str(), &status, 0);
        mono_image_close(image);

        // Don't forget to free the file data
        delete[] fileData;

        return assembly;
    }
}