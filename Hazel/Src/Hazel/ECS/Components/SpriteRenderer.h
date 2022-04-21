#pragma once
#include "Component.h"
#include "glm/glm.hpp"

namespace Hazel
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		SpriteRenderer(const glm::vec4& color);

		glm::vec4 GetColor() { return m_Color; }
		glm::vec4 GetColor() const { return m_Color; }

	private:
		glm::vec4 m_Color;
	};
}