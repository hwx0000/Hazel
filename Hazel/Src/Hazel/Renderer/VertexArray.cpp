#include "hzpch.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"
#include "glad/glad.h"

VertexArray* VertexArray::Create()
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
		glGenVertexArrays(1, &buffer->m_Index);
		glBindVertexArray(buffer->m_Index);

		break;
	}
	default:
		break;
	}

	return buffer;
}