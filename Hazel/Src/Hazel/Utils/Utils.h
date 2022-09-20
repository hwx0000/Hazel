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

		static const std::string& GetShaderTypeString(ShaderType type);

	private:
	};
}
