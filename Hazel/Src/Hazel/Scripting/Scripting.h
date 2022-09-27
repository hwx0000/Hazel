#pragma once
#include <string>
#include "mono/metadata/image.h"

namespace Hazel
{
	class Scripting
	{
	public:
		MonoAssembly* LoadCSharpAssembly(const std::string& assemblyPath);

		void PrintAssemblyTypes(MonoAssembly* assembly);

		// 根据C++这边输入的class name, 返回对应的MonoClass, 如果想在C++端创建C#上的对象, 需要借助此API
		MonoClass* GetClassInAssembly(MonoAssembly* assembly, const char* namespaceName, const char* className);

		void CreateInstanceInAssembly(MonoClass* p);
	};
}