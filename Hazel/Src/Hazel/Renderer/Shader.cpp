#include "hzpch.h"
#include "Shader.h"
#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{
	std::shared_ptr<Shader> Shader::Create(const std::string& path)
	{
		RendererAPI::APIType type = Renderer::GetAPI();
		switch (type)
		{
		case RendererAPI::APIType::OpenGL:
		{
			return std::make_shared<OpenGLShader>(path);
		}
		case RendererAPI::APIType::None:
			return nullptr;
		default:
			break;
		}

		return nullptr;
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& vertSource, const std::string& fragSource)
	{
		RendererAPI::APIType type = Renderer::GetAPI();
		switch (type)
		{
		case RendererAPI::APIType::OpenGL:
			return std::make_shared<OpenGLShader>(vertSource, fragSource);
		case RendererAPI::APIType::None:
			return nullptr;
		default:
			break;
		}

		return nullptr;
	}
}