#include "hzpch.h"
#include "UniformBuffer.h"
#include "Renderer/RendererAPI.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Hazel
{
	std::shared_ptr<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
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
			return std::make_shared<OpenGLUniformBuffer>(size, binding);
			break;
		}
		default:
			break;
		}

		return std::shared_ptr<UniformBuffer>();
	}
}
