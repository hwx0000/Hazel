#pragma once
#include <memory>
#include "Texture.h"
#include "glm/glm.hpp"

namespace Hazel 
{
	class SubTexture2D
	{
	public:
		SubTexture2D(const std::shared_ptr<Texture2D>& textureAtlas, const glm::vec2& minUV, const glm::vec2& maxUV);
		const std::shared_ptr<Texture2D>& GetTextureAtlas() { return m_TextureAtlas; }
		const glm::vec2* GetTexCoords() { return m_TexCoords; }


	private:
		std::shared_ptr<Texture2D> m_TextureAtlas;
		glm::vec2 m_TexCoords[4];
	};
}