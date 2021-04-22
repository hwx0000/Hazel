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


IndexBuffer* IndexBuffer::Create(int* indices, uint32_t size)
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
