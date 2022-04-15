#pragma once
#include "Renderer/Framebuffer.h"
#include "glad/glad.h"
#include "Renderer/Texture.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Hazel
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(uint32_t width, uint32_t height);
		~OpenGLFramebuffer() override;
		GLuint GetColorAttachmentId();

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void* GetColorAttachmentTexture2DId() override;
		virtual void ResizeColorAttachment(uint32_t width, uint32_t height) override;
		
	private:
		GLuint m_FramebufferId = -1;
		GLuint m_ColorAttachmentTextureId = -1;
	};
}