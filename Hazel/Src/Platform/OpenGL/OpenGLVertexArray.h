#pragma once
#include "Hazel/Renderer/VertexArray.h"

class OpenGLVertexArray : public VertexArray
{
public:
	OpenGLVertexArray();
	void Bind() const override;
	void Unbind() const override;
	void AddVertexBuffer(std::shared_ptr<VertexBuffer>&) override;
	void SetIndexBuffer(std::shared_ptr<IndexBuffer>&) override;

	const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override;
	const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override;
private:
	// һ��VAO������ȡ���VBO�������(VAO���������)
	std::vector<std::shared_ptr<VertexBuffer>>m_VertexBuffers;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	unsigned int m_Index;
};