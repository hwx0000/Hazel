#include "hzpch.h"
#include "OpenGLFramebuffer.h"

namespace Hazel
{
	// TODO: 这里绕开了Hazel对Texture的封装, 真的好吗？
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec) : Framebuffer(spec.width, spec.height)
	{
		//FBO的写法与VBO类似
		glGenFramebuffers(1, &m_FramebufferId);

		//可对绑定的Framebuffer(即fbo)进行读和写操作，最常用的一种
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferId);

		for (size_t i = 0; i < spec.colorAttachmentCnt; i++)
		{
			// 创建Texture2D作为framebuffer的output image
			GLuint textureId;
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);

			if(i == 0)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spec.width, spec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			else
				glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, spec.width, spec.height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, NULL);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			//attach it to the frame buffer, 作为输出的texture
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textureId, 0);
			m_ColorAttachmentTexIndices.push_back(textureId);
		}
		// Stencil和Depth Buffer的Attachment暂时不加了

		HAZEL_CORE_ASSERT((bool)(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE), "Framebuffer incomplete");

		const GLenum buffers[]{ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, buffers);
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_FramebufferId);

		for (GLuint id : m_ColorAttachmentTexIndices)
			glDeleteTextures(1, &id);
	}

	GLuint OpenGLFramebuffer::GetColorAttachmentId(uint32_t id)
	{
		return m_ColorAttachmentTexIndices[id];
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
#if _WIN64
		// 强行使用C++的四个转型字符, 就只能用这个了
		// TODO: 丑陋的代码
		// TODO: 这样做很危险, 因为void*在不同平台下字节数是不同的, 而m_ColorAttachmentTextureId类型始终是4个字节
		return reinterpret_cast<void*>((long long)m_ColorAttachmentTexIndices[0]);// 这里sizeof(long)返回4
		//return (void*)((long)m_ColorAttachmentTextureId);
#else
		return reinterpret_cast<void*>(m_ColorAttachmentTextureId);
#endif
	}

	void OpenGLFramebuffer::ResizeColorAttachment(uint32_t width, uint32_t height)
	{
		if (m_FramebufferId != -1)
		{
			m_Width = width;
			m_Height = height;

			// 注意, 这里不需要BindFramebuffer
			// TODO: TEMP
			glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentTexIndices[0]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		}
	}

	// 获取单点pixel的像素值
	int OpenGLFramebuffer::ReadPixel(uint32_t colorAttachmentId, int x, int y)
	{
		Bind();
		glReadBuffer(GL_COLOR_ATTACHMENT0 + colorAttachmentId);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;
	}
}