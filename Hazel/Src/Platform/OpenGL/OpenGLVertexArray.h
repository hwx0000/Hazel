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
	// �о���VAO��¼���������ã�ͦ��ֵģ���������������������巢������
	std::vector<VertexBuffer*>m_VertexBuffers;
	IndexBuffer* m_IndexBuffer;
};