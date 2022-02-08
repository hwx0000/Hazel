#pragma once
#include "Hazel/Renderer/Texture.h"

namespace Hazel
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);

		// Inherited via Texture2D
		virtual unsigned int GetWidth() override;
		virtual unsigned int GetHeight() override;
	private:
		int m_RendererID;
		unsigned int m_TextureID;
	};
}