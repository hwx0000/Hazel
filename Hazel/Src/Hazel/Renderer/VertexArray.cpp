#include "hzpch.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"
#include "glad/glad.h"

namespace Hazel
{
	VertexArray* VertexArray::Create()
	{
		VertexArray* buffer = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::APIType::None:
		{
			CORE_LOG_ERROR("No RendererAPI selected");
			HAZEL_ASSERT(false, "Error, please choose a Renderer API");
		}
		case RendererAPI::APIType::OpenGL:
		{
			buffer = (new OpenGLVertexArray());
		}
		}

		return buffer;
	}
}