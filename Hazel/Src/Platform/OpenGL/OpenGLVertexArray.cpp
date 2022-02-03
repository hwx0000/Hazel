#include "hzpch.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Hazel
{
	static GLenum GetShaderDataTypeToOpenGL(const ShaderDataType& type)
	{
		switch (type)
		{
		case ShaderDataType::FLOAT: return GL_FLOAT;
		case ShaderDataType::FLOAT2:return GL_FLOAT;
		case ShaderDataType::FLOAT3:return GL_FLOAT;
		case ShaderDataType::FLOAT4:return GL_FLOAT;
		}
		HAZEL_ASSERT(false, "Unknown Shader Data Type");
		return GL_FALSE;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_Index);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_Index);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_Index);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		HAZEL_CORE_ASSERT(vertexBuffer->GetBufferLayout().GetCount(), "Empty Layout in VertexBuffer!");
		// 挖VBO的数据到VAO时，要记得先Bind Vertex Array
		glBindVertexArray(m_Index);
		vertexBuffer->Bind();

		BufferLayout layout = vertexBuffer->GetBufferLayout();
		int index = 0;
		for (const BufferElement& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				GetShaderTypeDataCount(element.GetType()),
				GetShaderDataTypeToOpenGL(element.GetType()),
				element.IsNormalized() ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(element.GetOffset()));
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		// 先确保Bind
		glBindVertexArray(m_Index);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

	const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}
}
