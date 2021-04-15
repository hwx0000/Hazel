#pragma once
#include "Hazel/Renderer/VertexArray.h"

class OpenGLVertexArray : public VertexArray
{
public:
	void Bind() const override;
	void Unbind() const override;
	void AddVertexBuffer(std::shared_ptr<VertexBuffer>&) override;
	void AddIndexBuffer(std::shared_ptr<IndexBuffer>&) override;

private:
	// 感觉用VAO记录这俩的引用，挺奇怪的，反正先声明在这里，不具体发生作用
	std::vector<VertexBuffer*>m_VertexBuffers;
	IndexBuffer* m_IndexBuffer;
};