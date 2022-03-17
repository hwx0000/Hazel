#include "hzpch.h"
#include "OpenGLTexture2D.h"
#include "glad/glad.h"
#include "stb_image.cpp"
#include "Core/Core.h"

namespace Hazel
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(true);

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int channels;
		unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &channels, 0);
		HAZEL_ASSERT(data, "Failed to load texture!")

		switch (channels)
		{
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			break;
		case 4:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			break;
		default:
			HAZEL_ASSERT(0, "Unsupported texture format!")
			break;
		}

		//glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		
		// 注意格式是GL_RGBA8
		glTextureStorage2D(m_TextureID, 1, GL_RGBA8, m_Width, m_Height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}


	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	unsigned int OpenGLTexture2D::GetWidth()
	{
		return m_Width;
	}

	unsigned int OpenGLTexture2D::GetHeight()
	{
		return m_Height;
	}

	void OpenGLTexture2D::Bind(uint32_t slot)
	{
		// 老式的写法是这样
		glActiveTexture(GL_TEXTURE0);// todo, 多个Texture的时候有问题
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		
		// 下面这种写法是Cherno的写法, 但是好像我的台式可以运行这个代码
		// 但是笔记本运行就会有问题...
		//glBindTextureUnit(slot, m_TextureID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		// bpp: bytes per pixel
		uint32_t bpp = 4;// 默认是用RGBA的格式
		HAZEL_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		// 可以通过glTextureSubImage2D这个API，为Texture手动提供数据，创建这个WhiteTexture
		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
}
