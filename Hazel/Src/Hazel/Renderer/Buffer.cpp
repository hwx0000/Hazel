#include "hzpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"// �����cpp�������������ͷ�ļ�
#include "Glad/glad.h"


// ע������Ϊstatic�ĺ������ڶ����ʱ����Ҫдstatic�ؼ���
// �������Create�������ڻ��ඨ��ģ���Ϊ�����Ĵ��ڶ���Ӧ�ð�������ƽ̨��������������Էŵ��˻�����
// ������������cpp��������ص��������ͷ�ļ�
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
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);//��CPU������GPU

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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);//��CPU������GPU

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
