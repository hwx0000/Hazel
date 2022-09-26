#include "hzpch.h"
#include "Framebuffer.h"
#include "Renderer/RendererAPI.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Hazel
{
	std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::APIType::None:
		{
			CORE_LOG_ERROR("No RendererAPI selected");
			HAZEL_ASSERT(false, "Error, please choose a Renderer API");
			break;
		}
		case RendererAPI::APIType::OpenGL:
		{
			return std::make_shared<OpenGLFramebuffer>(spec);
			break;
		}
		default:
			break;
		}

		return std::shared_ptr<Framebuffer>();
	}
}
