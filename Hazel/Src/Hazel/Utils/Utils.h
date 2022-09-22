#pragma once
#include <string>
#include "Hazel/Renderer/Shader.h"
#include <shaderc/shaderc.hpp>

namespace Hazel
{
	class Utils
	{
	public:
		// 由于是HazelEditor启动的, 所以记录的是相对于HazelEditor.vcxproj的相对路径
		static const char* GetShaderCacheRelativeDirectory()
		{
			return "Cache\\ShaderCache";
		}

		static std::string GetCurrentDirectory();

		static std::string ShaderTypeToString(ShaderType type);
		static ShaderType GetShaderTypeFromString(const std::string& typeName);

		static shaderc_shader_kind ShaderTypeToShaderCKind(ShaderType type);

	private:
	};
}
