#include "hzpch.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"

VertexArray* Create()
{
	VertexArray* buffer = nullptr;
	switch (Renderer::GetAPI())
	{
	case RendererAPI::None:
	{
		CORE_LOG_ERROR("No RendererAPI selected");
		HAZEL_ASSERT(false, "Error, please choose a Renderer API");
		break;
	}
	case RendererAPI::OpenGL:
	{
		buffer = (new OpenGLVertexArray());
		buffer->Bind();

		break;
	}
	default:
		break;
	}

	return buffer;
}