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
	    mono_set_assemblies_path("../Hazel/vendor/Mono/DotNetLibs/4.5");
    
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

    // iterate through all the type definitions in our assembly
    void Scripting::PrintAssemblyTypes(MonoAssembly* assembly)
    {
        MonoImage* image = mono_assembly_get_image(assembly);

        // 从assembly的meta信息里读取meta data table, 这里读取的是Type对应的Table, 表里的每一行
        // 代表一个Type
        const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
        int32_t numTypes = mono_table_info_get_rows(typeDefinitionsTable);

        // 遍历Table里的每行, 这里的numTypes最小为1, 因为C#的DLL和EXEs默认都会有一个Module类型的Type, 代表整个
        // assembly的module
        for (int32_t i = 1; i < numTypes; i++)
        {
            // 每一行的每列元素记录了Type的相关信息, 比如namespace和type name
            uint32_t cols[MONO_TYPEDEF_SIZE];
            mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

            // 还可以获取field list和method list等
            const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
            const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);

            printf("%s.%s\n", nameSpace, name);
        }
    }
}