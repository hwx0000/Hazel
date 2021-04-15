#include "hzpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"// 基类的cpp引用了派生类的头文件
#include "Glad/glad.h"


// 注意声明为static的函数，在定义的时候不需要写static关键字
// 而且这个Create函数是在基类定义的，因为创建的窗口对象应该包含多种平台的派生类对象，所以放到了基类里
// 而且这个基类的cpp引用了相关的派生类的头文件
VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
{
	VertexBuffer* buffer = nullptr;
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
		buffer = (new OpenGLVertexBuffer());
		glGenBuffers(1, &buffer->m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer->m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);//从CPU传入了GPU

		break;
	}
	default:
		break;
	}

	return buffer;
}


IndexBuffer* IndexBuffer::Create(int* indices, uint32_t size)
{
	IndexBuffer* buffer = nullptr;
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
		buffer = (new OpenGLIndexBuffer());
		glGenBuffers(1, &buffer->m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);//从CPU传入了GPU

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
