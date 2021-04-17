#pragma once
#include "Hazel/Renderer/VertexArray.h"

class OpenGLVertexArray : public VertexArray
{
public:
	OpenGLVertexArray();
	void Bind() const override;
	void Unbind() const override;
	void AddVertexBuffer(std::shared_ptr<VertexBuffer>&) override;
	void AddIndexBuffer(std::shared_ptr<IndexBuffer>&) override;

private:
	// һ��VAO������ȡ���VBO�������(VAO���������)
	std::vector<std::shared_ptr<VertexBuffer>>m_VertexBuffers;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	unsigned int m_Index;
};