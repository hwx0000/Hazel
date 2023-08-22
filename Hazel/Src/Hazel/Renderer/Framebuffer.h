#pragma once
#include <memory>
#include "Shader.h"

namespace Hazel 
{
	struct FramebufferSpecification
	{
		uint32_t width = 800;
		uint32_t height = 600;
		int32_t colorAttachmentCnt = 1;
		int32_t depthAttachmentCnt = -1;
		int32_t stencilAttachmentCnt = -1;
		bool enableMSAA;
	};

	class Framebuffer
	{
	public:
		static std::shared_ptr<Framebuffer> Create(const FramebufferSpecification& spec);
		Framebuffer(uint32_t w, uint32_t h) : m_Width(w), m_Height(h) {}
		virtual ~Framebuffer() = default;

		virtual uint32_t GetFramebufferId() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void ResizeColorAttachment(uint32_t width, uint32_t height) = 0;
		virtual void* GetColorAttachmentTexture2DId() = 0;
		virtual void SetColorAttachmentTexture2DId(uint32_t id, uint32_t value) = 0;
		virtual int ReadPixel(uint32_t colorAttachmentId, int x, int y) = 0;
		virtual void SetShader(const std::shared_ptr<Shader>& s) { m_Shader = s; }
		virtual std::shared_ptr<Shader>& GetShader() { return m_Shader; }
		virtual void SetUpMSAAContext() = 0;
		virtual void ResolveMSAATexture(uint32_t width, uint32_t height) = 0;

	protected:
		uint32_t m_Width = 800;
		uint32_t m_Height = 600;
		bool m_ShowOnScreen = false;
		std::shared_ptr<Shader> m_Shader;
	};
	
}