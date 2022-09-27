#pragma once
#include <string>
#include "mono/metadata/image.h"

namespace Hazel
{
	// 类似于Unity, C#这边的脚本层分为核心层和用户层两块
	// 核心层的代码(C#这边的源码)应该是和C++的代码会存在相互调用的情况的
	class Scripting
	{
	public:
		MonoAssembly* LoadCSharpAssembly(const std::string& assemblyPath);

		void PrintAssemblyTypes(MonoAssembly* assembly);

		// 根据C++这边输入的class name, 返回对应的MonoClass, 如果想在C++端创建C#上的对象, 需要借助此API
		MonoClass* GetClassInAssembly(MonoAssembly* assembly, const char* namespaceName, const char* className);

		MonoObject* CreateInstance(MonoClass* p);

		// Mono gives us two ways of calling C# methods: mono_runtime_invoke and Unmanaged Method Thunks. 
		// This Api will only cover mono_runtime_invoke

		// Using mono_runtime_invoke is slower compared to Unmanaged Method Thunks, but it's also safe and more flexible. 
		// mono_runtime_invoke can invoke any method with any parameters, and from what I understand mono_runtime_invoke also does a lot more error checking and validation on the object you pass, as well as the parameters.

		// 在编译期不知道Method签名时, 适合用mono_runtime_invoke, 每秒高频率调用(10fps)的Method适合用Unmanaged Method Thunks, 
		void CallMethod(MonoObject* instance, const std::string& methodName);

		void GetFieldRef();
	};
}