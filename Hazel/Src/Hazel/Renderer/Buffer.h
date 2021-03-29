#pragma once

class VertexBuffer
{
public:
	virtual ~VertexBuffer() {};
	virtual void Bind() const = 0;// 别忘了加const
	virtual void Unbind() const = 0;
	static VertexBuffer* Create(float* vertices, uint32_t size);
protected:
	uint32_t m_VertexBuffer;
};

class IndexBuffer
{
public:
	virtual ~IndexBuffer() = 0;
	virtual void Bind() const = 0;// 别忘了加const
	virtual void Unbind() const = 0;
	static IndexBuffer* Create(int* indices, uint32_t size);
protected:
	uint32_t m_IndexBuffer;
};