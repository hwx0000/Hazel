#pragma once
#include <string>
#include "mono/metadata/image.h"
#include "mono/jit/jit.h"

namespace Hazel
{
	// 此类负责在C++端调用C#端的代码, 比如Call Method, 读写Property和Field的值等操作
	// 类似于Unity, C#这边的脚本层分为核心层和用户层两块
	// 核心层的代码(C#这边的源码)应该是和C++的代码会存在相互调用的情况的
	class Scripting
	{
	public:
		// C++端读取C#这边的Assembly(以MonoAssembly的形式)
		MonoAssembly* LoadCSharpAssembly(const std::string& assemblyPath);

		void PrintAssemblyTypes(MonoAssembly* assembly);

		// 根据C++这边输入的class name, 返回对应的MonoClass, 如果想在C++端创建C#上的对象, 需要借助此API
		MonoClass* GetClassInAssembly(MonoAssembly* assembly, const char* namespaceName, const char* className);

		// C++创建C#这边的对象
		MonoObject* CreateInstance(MonoClass* p);

		// C++调用C#这边的Method
		void CallMethod(MonoClass* monoClass, MonoObject* instance, const char* methodName);

		// Field can be public or private
		MonoClassField* GetFieldRef(MonoObject* instance, const char* fieldName);

		template<class T>
		const T& GetFieldValue(MonoObject* instance, MonoClassField* field)
		{
			T value;
			mono_field_get_value(instance, field, &value);
			return value;
		}

		MonoProperty* GetPropertyRef(MonoObject* instance, const char* fieldName);

		template<class T>
		const T& GetPropertyValue(MonoObject* instance, MonoProperty* prop)
		{
			T value;
			mono_property_get_value(instance, prop, &value);
			return value;
		}
	};
}