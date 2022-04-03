#pragma once
#include "Hazel/Renderer/Buffer.h"

namespace Hazel
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);				// static buffer
		OpenGLVertexBuffer(uint32_t size);								// dynamic buffer
		virtual ~OpenGLVertexBuffer() override;
		void Bind()const override;// 别忘了加const
		void Unbind() const override;
		void SetData(uint32_t pos, void* data, uint32_t len) override;
		BufferLayout& GetBufferLayout() override
		{
			return m_Layout;
		}

		void SetBufferLayout(const BufferLayout& layout) override
		{
			m_Layout = layout;
		}

	private:
		uint32_t m_VertexBuffer;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* vertices, uint32_t size);	// Static
		virtual ~OpenGLIndexBuffer() override;
		uint32_t GetCount() const override;
		void Bind()const override;// 别忘了加const
		void Unbind() const override;
	private:
		uint32_t m_Count;
		uint32_t m_IndexBuffer;
	};
}