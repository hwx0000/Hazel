#include "hzpch.h"
#include "Hazel/Utils/Utils.h"
#include "mono/metadata/assembly.h"
#include "mono/metadata/image.h"
#include "Scripting.h"

namespace Hazel
{
    // 读取一个C# dll到Mono里, 然后返回对应的Assembly指针
    MonoAssembly* Scripting::LoadCSharpAssembly(const std::string& assemblyPath)
    {
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