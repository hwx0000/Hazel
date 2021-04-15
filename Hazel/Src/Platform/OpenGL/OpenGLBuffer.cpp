#include "hzpch.h"
#include "OpenGLBuffer.h"
#include "glad/glad.h"

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
}

void OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
}

void OpenGLVertexBuffer::Unbind()const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
}

void OpenGLIndexBuffer::Unbind()const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}