#pragma once
#include "Hazel/Renderer/Texture.h"

namespace Hazel
{
	class OpenGLTextureCube : public TextureCube
	{
	public:
		OpenGLTextureCube(const std::vector<std::string>& facesPath);
		~OpenGLTextureCube();

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