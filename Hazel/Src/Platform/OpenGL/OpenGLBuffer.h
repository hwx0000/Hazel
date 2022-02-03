#pragma once
#include "Hazel/Renderer/Buffer.h"

namespace Hazel
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
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
		uint32_t m_VertexBuffer;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(int* vertices, uint32_t size);
		virtual ~OpenGLIndexBuffer() override;
		uint32_t GetCount() const override;
		void Bind()const override;// 别忘了加const
		void Unbind() const override;
	private:
		uint32_t m_Count;
		uint32_t m_IndexBuffer;
	};
}