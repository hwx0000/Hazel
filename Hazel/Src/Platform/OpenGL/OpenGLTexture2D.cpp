#include "hzpch.h"
#include "OpenGLTexture2D.h"
#include "glad/glad.h"
#include "stb_image.h"
#include "Hazel/Core.h"

namespace Hazel
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, channels;
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		HAZEL_ASSERT(data, "Failed to load texture!")

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	unsigned int OpenGLTexture2D::GetWidth()
	{
		return 0;
	}

	unsigned int OpenGLTexture2D::GetHeight()
	{
		return 0;
	}
}
