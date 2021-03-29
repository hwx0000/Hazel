#pragma once
#include "Hazel/Renderer/Buffer.h"

class OpenGLVertexBuffer : public VertexBuffer 
{
public:
	virtual ~OpenGLVertexBuffer() override {}
	void Bind()const override;// 别忘了加const
	void Unbind() const override;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
	virtual ~OpenGLIndexBuffer() override {}
	void Bind()const override;// 别忘了加const
	void Unbind() const override;
};