#include "hzpch.h"
#include "Utils.h"

namespace Hazel
{
	const std::string& Utils::GetShaderTypeString(ShaderType type)
	{
		switch (type)
		{
		case Hazel::ShaderType::Vertex:
			return "Vertex";
		case Hazel::ShaderType::Fragement:
			return "Fragement";
		case Hazel::ShaderType::Geometry:
			return "Geometry";
		case Hazel::ShaderType::Compute:
			return "Compute";
		default:
			return "";
		}
	}
}