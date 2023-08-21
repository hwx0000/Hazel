#include "hzpch.h"
#include "OpenGLFramebuffer.h"
#include "Hazel/Renderer/Shader.h"

namespace Hazel
{
	// TODO: 这里绕开了Hazel对Texture的封装, 真的好吗？
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec) : Framebuffer(spec.width, spec.height)
	{
		//FBO的写法与VBO类似
		glGenFramebuffers(1, &m_FramebufferId);

		//可对绑定的Framebuffer(即fbo)进行读和写操作，最常用的一种
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferId);

		m_EnableMSAA = spec.enableMSAA;

		if (!m_EnableMSAA)
		{
			for (size_t i = 0; i < spec.colorAttachmentCnt; i++)
			{
				// 创建Texture2D作为framebuffer的output image
				GLuint textureId;
				glGenTextures(1, &textureId);
				glBindTexture(GL_TEXTURE_2D, textureId);

				// TODO: 这样写死并不合适
				if (i == 0)
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spec.width, spec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
				else
					// R32I应该是代表32位interger, 意思是这32位都只存一个integer
					glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, spec.width, spec.height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, NULL);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

				//attach it to the frame buffer, 作为输出的texture
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textureId, 0);
				m_ColorAttachmentTexIndices.push_back(textureId);
			}
		}
		else
		{
			// 1.       
			{
				// 创建Texture2D作为framebuffer的output image
				GLuint textureId;
				glGenTextures(1, &textureId);
				glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureId);
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA, spec.width, spec.height, GL_TRUE);

				glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureId, 0);

				m_ColorAttachmentTexIndices.push_back(textureId);
			}

			// 2. 
			if(true)
			{
				
				// 创建Texture2D作为framebuffer的output image
				GLuint textureId;
				glGenTextures(1, &textureId);
				glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureId);
				// 注意, 这里的samples数必须跟前面Attachment的Samples数一致, 否则会显示Incomplete Framebuffer
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_R32I, spec.width, spec.height, GL_TRUE);

				glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 1);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D_MULTISAMPLE, textureId, 0);

				m_ColorAttachmentTexIndices.push_back(textureId);

				/*
				// 创建Texture2D作为framebuffer的output image
				GLuint textureId;
				glGenTextures(1, &textureId);
				glBindTexture(GL_TEXTURE_2D, textureId);

				// R32I应该是代表32位interger, 意思是这32位都只存一个integer
				glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, spec.width, spec.height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, NULL);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);

				m_ColorAttachmentTexIndices.push_back(textureId);
				*/
			}
		}
		// Stencil和Depth Buffer的Attachment暂时不加了

		HAZEL_CORE_ASSERT((bool)(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE), "Framebuffer incomplete");

		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferId);


		// 目前每个Camera只output两张贴图, 第一张代表Viewport里的贴图, 第二张代表InstanceID贴图
		const GLenum buffers[]{ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, buffers);

		//const GLenum buffers[]{ GL_COLOR_ATTACHMENT0 };
		//glDrawBuffers(1, buffers);
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
		if (m_EnableMSAA)
			return (void*)m_MSAATexId;
		
		//OpenGLShader* glShader = (OpenGLShader*)&*m_ViewportDrawData.m_Shader;
		//ImGui::Image((void*)glShader->screenTexture, size, { 0,1 }, { 1,0 });


#if _WIN64
		// 强行使用C++的四个转型字符, 就只能用这个了
		// TODO: 丑陋的代码
		// TODO: 这样做很危险, 因为void*在不同平台下字节数是不同的, 而m_ColorAttachmentTextureId类型始终是4个字节
		return reinterpret_cast<void*>((long long)m_ColorAttachmentTexIndices[0]);// 这里sizeof(long)返回4
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
			if (!m_EnableMSAA)
			{
				glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentTexIndices[0]);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

				//glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentTexIndices[1]);
				//glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, NULL);

				//glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentTexIndices[0]);
				//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_ColorAttachmentTexIndices[0]);
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA, width, height, GL_TRUE);
				//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_ColorAttachmentTexIndices[0], 0);


				//glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_R32I, spec.width, spec.height, GL_TRUE);
				//glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 1);
				//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D_MULTISAMPLE, textureId, 0);

				glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_ColorAttachmentTexIndices[1]);
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_R32I, width, height, GL_TRUE);
				//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D_MULTISAMPLE, m_ColorAttachmentTexIndices[1], 0);
			}
		}
	}

	// 获取单点pixel的像素值
	int OpenGLFramebuffer::ReadPixel(uint32_t frameBufferID, int x, int y)
	{
		if (m_EnableMSAA)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
			glViewport(0, 0, m_Width, m_Height);
			glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentTexIndices[1]);
			glReadBuffer(GL_COLOR_ATTACHMENT1);
			int pixelData;
			glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
			return pixelData;
		}
		else
		{
			Bind();
			glReadBuffer(GL_COLOR_ATTACHMENT0 + frameBufferID);
			int pixelData;
			glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
			return pixelData;
		}
	}

	uint32_t OpenGLFramebuffer::GetFramebufferId()
	{
		return m_FramebufferId;
	}
}