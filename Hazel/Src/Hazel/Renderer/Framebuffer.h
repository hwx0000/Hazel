#pragma once
#include <memory>

namespace Hazel 
{
	class Framebuffer
	{
	public:
		static std::shared_ptr<Framebuffer>Create(uint32_t width, uint32_t height);
		Framebuffer(uint32_t w, uint32_t h) : m_Width(), m_Height(h) {}
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void ResizeColorAttachment(uint32_t width, uint32_t height) = 0;
		virtual void* GetColorAttachmentTexture2DId() = 0;

	protected:
		uint32_t m_Width = 800;
		uint32_t m_Height = 600;
		bool m_ShowOnScreen = false;
	};
	
}