#include "hzpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"// 基类的cpp引用了派生类的头文件
#include "Glad/glad.h"

namespace Hazel
{
	// 注意声明为static的函数，在定义的时候不需要写static关键字
	// 而且这个Create函数是在基类定义的，因为创建的窗口对象应该包含多种平台的派生类对象，所以放到了基类里
	// 而且这个基类的cpp引用了相关的派生类的头文件
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		VertexBuffer* buffer = nullptr;
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
			buffer = (new OpenGLVertexBuffer(vertices, size));

			break;
		}
		default:
			break;
		}

		return buffer;
	}

	VertexBuffer* VertexBuffer::Create(uint32_t size)
	{
		VertexBuffer* buffer = nullptr;
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
			buffer = (new OpenGLVertexBuffer(size));

			break;
		}
		default:
			break;
		}

		return buffer;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		IndexBuffer* buffer = nullptr;
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
			buffer = (new OpenGLIndexBuffer(indices, size));

			break;
		}
		default:
			break;
		}

		return buffer;
	}

	void BufferLayout::CalculateElementsOffsets()
	{
		m_Stride = 0;
		for (auto &element : m_Elements)
		{
			element.SetOffset(m_Stride);
			m_Stride += element.GetSize();
		}
	}

	bool BufferElement::IsIntergerType() const
	{
		if (m_Type == ShaderDataType::INT) 
			return true;
		
		return false;
	}
}
