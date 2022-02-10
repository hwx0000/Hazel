#include "hzpch.h"
#include "Shader.h"
#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{
	Shader* Shader::Create(const std::string& path)
	{
		RendererAPI::APIType type = Renderer::GetAPI();
		switch (type)
		{
		case RendererAPI::APIType::OpenGL:
			return new OpenGLShader(path);
		case RendererAPI::APIType::None:
			return nullptr;
		default:
			break;
		}

		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertSource, const std::string& fragSource)
	{
		RendererAPI::APIType type = Renderer::GetAPI();
		switch (type)
		{
		case RendererAPI::APIType::OpenGL:
			return new OpenGLShader(vertSource, fragSource);
		case RendererAPI::APIType::None:
			return nullptr;
		default:
			break;
		}

		return nullptr;
	}
}