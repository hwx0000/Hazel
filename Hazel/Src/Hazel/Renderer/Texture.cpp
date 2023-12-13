#include "hzpch.h"
#include "Hazel/Renderer/RendererAPI.h"
#include "Texture.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"
#include "Platform/OpenGL/OpenGLTextureCube.h"

namespace Hazel
{
	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (RendererAPI::GetAPIType())
		{
		case RendererAPI::APIType::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		case RendererAPI::APIType::None:
		{
			CORE_LOG_ERROR("No RendererAPI selected");
			HAZEL_ASSERT(false, "Error, please choose a Renderer API");
			return nullptr;
		}
		default:
			break;
		}

		return nullptr;
	}

	std::shared_ptr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (RendererAPI::GetAPIType())
		{
		case RendererAPI::APIType::OpenGL:
			return std::make_shared<OpenGLTexture2D>(width, height);
		case RendererAPI::APIType::None:
		{
			CORE_LOG_ERROR("No RendererAPI selected");
			HAZEL_ASSERT(false, "Error, please choose a Renderer API");
			return nullptr;
		}
		default:
			break;
		}

		return nullptr;
	}

	std::shared_ptr<TextureCube> TextureCube::Create(const std::vector<std::string>& facesPath)
	{
		switch (RendererAPI::GetAPIType())
		{
		case RendererAPI::APIType::OpenGL:
			return std::make_shared<OpenGLTextureCube>(facesPath);
		case RendererAPI::APIType::None:
		{
			CORE_LOG_ERROR("No RendererAPI selected");
			HAZEL_ASSERT(false, "Error, please choose a Renderer API");
			return nullptr;
		}
		default:
			break;
		}

		return nullptr;
	}
}