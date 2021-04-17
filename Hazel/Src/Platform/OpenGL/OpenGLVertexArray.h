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
	// 一个VAO可以挖取多个VBO里的数据(VAO存的是引用)
	std::vector<std::shared_ptr<VertexBuffer>>m_VertexBuffers;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	unsigned int m_Index;
};