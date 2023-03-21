#pragma once
#include "Component.h"
#include "Hazel/Renderer/Texture.h"
#include "glm/glm.hpp"

namespace Hazel
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		SpriteRenderer(const glm::vec4& color);

		glm::vec4& GetTintColor() { return m_TintColor; }
		const glm::vec4& GetTintColor() const { return m_TintColor; }

		std::shared_ptr<Texture2D> GetTexture() { return m_Texture; }
		const std::shared_ptr<Texture2D> GetTexture() const { return m_Texture; }

		void SetTexture(const std::shared_ptr<Texture2D> ref) {  m_Texture = ref; }

		glm::vec2& GetTilingFactor() { return m_TilingFactor; }
		glm::vec2 GetTilingFactor() const { return m_TilingFactor; }

	private:
		std::shared_ptr<Texture2D> m_Texture;
		glm::vec4 m_TintColor = { 0, 0, 0, 255 };
		glm::vec2 m_TilingFactor = {1.0f, 1.0f};
	};
}