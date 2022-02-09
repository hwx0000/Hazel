#include "hzpch.h"
#include "OpenGLTexture2D.h"
#include "glad/glad.h"
#include "stb_image.cpp"
#include "Hazel/Core.h"

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
		//// 老式的写法是这样
		//glActiveTexture(GL_TEXTURE0);// todo, 多个Texture的时候有问题
		//glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glBindTextureUnit(slot, m_TextureID);
	}
}
