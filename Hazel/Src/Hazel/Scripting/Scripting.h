#pragma once
#include <string>
#include "mono/metadata/image.h"

namespace Hazel
{
	class Scripting
	{
	public:
		MonoAssembly* LoadCSharpAssembly(const std::string& assemblyPath);
	};
}