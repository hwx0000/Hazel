#pragma once
#include "Hazel/Renderer/Texture.h"

namespace Hazel
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		~OpenGLTexture2D();

		// Inherited via Texture2D
		unsigned int GetWidth() override;
		unsigned int GetHeight() override;
		void* GetTextureId() override;
		void SetData(void* data, uint32_t size) override;
		void Bind(uint32_t slot) override;

	private:
		unsigned int m_TextureID;
		int m_Width;
		int m_Height;
	};
}