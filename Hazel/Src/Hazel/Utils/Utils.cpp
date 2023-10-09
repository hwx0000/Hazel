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

	shaderc_shader_kind Utils::ShaderTypeToShaderCKind(ShaderType type)
	{
		switch (type)
		{
		case Hazel::ShaderType::InValid:
			return shaderc_shader_kind();
		case Hazel::ShaderType::Vertex:
			return shaderc_shader_kind::shaderc_vertex_shader;
		case Hazel::ShaderType::Fragement:
			return shaderc_shader_kind::shaderc_fragment_shader;
		case Hazel::ShaderType::Compute:
			return shaderc_shader_kind::shaderc_compute_shader;
		case Hazel::ShaderType::Geometry:
			return shaderc_shader_kind::shaderc_geometry_shader;
		default:
			return shaderc_shader_kind();
		}
	}

	GLenum Utils::ShaderTypeToOpenGL(ShaderType type)
	{
		switch (type)
		{
		case Hazel::ShaderType::InValid:
			return GL_INVALID_ENUM;
		case Hazel::ShaderType::Vertex:
			return GL_VERTEX_SHADER;
		case Hazel::ShaderType::Fragement:
			return GL_FRAGMENT_SHADER;
		case Hazel::ShaderType::Compute:
			return GL_COMPUTE_SHADER;
		case Hazel::ShaderType::Geometry:
			return GL_GEOMETRY_SHADER;
		default:
			return GL_INVALID_ENUM;
		}
	}

	char* Utils::ReadBytes(const std::string& filepath, uint32_t* outSize)
	{
		std::ifstream stream(filepath, std::ios::binary | std::ios::ate);

		if (!stream)
		{
			LOG_ERROR("Failed to open the file:" + filepath);
			return nullptr;
		}

		std::streampos end = stream.tellg();
		stream.seekg(0, std::ios::beg);
		uint32_t size = (uint32_t)(end - stream.tellg());

		if (!size)
		{
			LOG("File is empty:" + filepath);
			return nullptr;
		}

		char* buffer = new char[size];
		stream.read((char*)buffer, size);
		stream.close();

		*outSize = size;
		return buffer;
	}

	std::string Utils::GetCurrentDirectory()
	{
		return std::filesystem::current_path().string();
	}
}