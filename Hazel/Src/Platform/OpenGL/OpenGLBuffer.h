#pragma once
#include "Hazel/Renderer/Buffer.h"

class OpenGLVertexBuffer : public VertexBuffer 
{
public:
	virtual ~OpenGLVertexBuffer() override;
	void Bind()const override;// 别忘了加const
	void Unbind() const override;
	BufferLayout& GetBufferLayout() override 
	{
		return m_Layout;
	}

	void SetBufferLayout(const BufferLayout& layout) override
	{
		m_Layout = layout;
	}

private:
	BufferLayout m_Layout;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
	virtual ~OpenGLIndexBuffer() override {}
	void Bind()const override;// 别忘了加const
	void Unbind() const override;
};