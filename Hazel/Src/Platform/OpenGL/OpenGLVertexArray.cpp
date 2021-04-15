#include "hzpch.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"

void OpenGLVertexArray::Bind() const
{
	glGenVertexArrays(1, &(GLuint)m_Index);
	glBindVertexArray(m_Index);
	glBindVertexArray(0);
}

void OpenGLVertexArray::Unbind() const
{
}

void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer)
{
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
}
