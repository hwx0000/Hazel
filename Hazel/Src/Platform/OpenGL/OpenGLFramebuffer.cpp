#include "hzpch.h"
#include "OpenGLFramebuffer.h"

namespace Hazel
{
	// TODO: 这里绕开了Hazel对Texture的封装, 真的好吗？
	OpenGLFramebuffer::OpenGLFramebuffer(uint32_t width, uint32_t height) : Framebuffer(width, height)
	{
		//FBO的写法与VBO类似
		glGenFramebuffers(1, &m_FramebufferId);

		//可对绑定的Framebuffer(即fbo)进行读和写操作，最常用的一种
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferId);

		// 创建Texture2D作为framebuffer的output image
		glGenTextures(1, &m_ColorAttachmentTextureId);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentTextureId);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		//attach it to the frame buffer, 作为输出的texture
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachmentTextureId, 0);

		// Stencil和Depth Buffer的Attachment暂时不加了

		HAZEL_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer incomplete");
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_FramebufferId);
		glDeleteTextures(1, &m_ColorAttachmentTextureId);
	}

	GLuint OpenGLFramebuffer::GetColorAttachmentId()
	{
		return m_ColorAttachmentTextureId;
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferId);
		glViewport(0, 0, m_Width, m_Height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void* OpenGLFramebuffer::GetColorAttachmentTexture2DId()
	{
		// 强行使用C++的四个转型字符, 就只能用这个了
		// TODO: 丑陋的代码
		return reinterpret_cast<void*>(m_ColorAttachmentTextureId);
		//return (void*)(m_ColorAttachmentTextureId);
	}

	void OpenGLFramebuffer::ResizeColorAttachment(uint32_t width, uint32_t height)
	{
		if (m_FramebufferId != -1)
		{
			m_Width = width;
			m_Height = height;

			// 注意, 这里不需要BindFramebuffer
			glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentTextureId);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		}
	}
}