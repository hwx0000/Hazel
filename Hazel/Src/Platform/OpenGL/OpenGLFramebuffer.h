#pragma once
#include "Renderer/Framebuffer.h"
#include "glad/glad.h"
#include "Renderer/Texture.h"
#include "OpenGLTexture2D.h"
#include "OpenGLShader.h"

namespace Hazel
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification&);
		~OpenGLFramebuffer() override;
		// get the n th color attachment id in OpenGL
		GLuint GetColorAttachmentId(uint32_t id);

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void* GetColorAttachmentTexture2DId() override;
		virtual void ResizeColorAttachment(uint32_t width, uint32_t height) override;
		virtual int ReadPixel(uint32_t colorAttachmentId, int x, int y) override;
		virtual uint32_t GetFramebufferId() override;
		void SetMSAATexID(const GLuint& id) { m_MSAATexId = id; }

	private:
		GLuint m_FramebufferId;
		GLuint m_FramebufferTempId;
		GLuint m_FramebufferTempTex;
		std::vector<GLuint> m_ColorAttachmentTexIndices;
		bool m_EnableMSAA;

		GLuint m_MSAATexId;
	};
}