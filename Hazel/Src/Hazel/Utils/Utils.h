#pragma once
#include <string>
#include "Hazel/Renderer/Shader.h"

namespace Hazel
{
	class Utils
	{
	public:
		static const char* GetShaderCacheDirectory()
		{
			return "Cache/ShaderCache";
		}

		static std::string GetCurrentDirectory();

		static std::string ShaderTypeToString(ShaderType type);
		static ShaderType GetShaderTypeFromString(const std::string& typeName);

	private:
	};
}
