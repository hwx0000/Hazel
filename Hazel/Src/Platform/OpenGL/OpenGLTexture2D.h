#pragma once
#include "Hazel/Renderer/Texture.h"

namespace Hazel
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		~OpenGLTexture2D();

		// Inherited via Texture2D
		virtual unsigned int GetWidth() override;
		virtual unsigned int GetHeight() override;

		virtual void Bind(uint32_t slot) override;
	private:
		unsigned int m_TextureID;
		int m_Width;
		int m_Height;
	};
}