#pragma once
#include "Renderer/Framebuffer.h"
#include "glad/glad.h"
#include "Renderer/Texture.h"

namespace Hazel
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(uint32_t width, uint32_t height);
		GLuint GetColorAttachmentId();

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void* GetColorAttachmentTexture2DId() override;
	private:
		GLuint m_FramebufferId;
		GLuint m_ColorAttachmentTextureId;
	};
}