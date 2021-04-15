#pragma once
#include "Hazel/Renderer/Buffer.h"
#include <memory>

class VertexArray 
{
public:
	virtual ~VertexArray();
	virtual void Bind()const = 0;
	virtual void Unbind()const = 0;

	virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>&) = 0;
	virtual void AddIndexBuffer(std::shared_ptr<IndexBuffer>&) = 0;

	static VertexArray* Create();
protected:
		uint32_t m_Index;
};