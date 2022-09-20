#include "hzpch.h"
#include "Utils.h"
#include <filesystem>

namespace Hazel
{
	std::string Utils::ShaderTypeToString(ShaderType type)
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

	ShaderType Utils::GetShaderTypeFromString(const std::string& typeName)
	{
		if (typeName == "Fragment" || typeName == "FRAGMENT" || typeName == "fragment")
			return ShaderType::Fragement;
		if (typeName == "Vertex" || typeName == "VERTEX" || typeName == "vertex")
			return ShaderType::Vertex;
		if (typeName == "Geometry" || typeName == "FRAGMENT" || typeName == "geometry")
			return ShaderType::Geometry;
		if (typeName == "Compute" || typeName == "COMPUTE" || typeName == "compute")
			return ShaderType::Compute;

		return ShaderType::InValid;
	}

	std::string Utils::GetCurrentDirectory()
	{
		return std::filesystem::current_path().string();
	}
}