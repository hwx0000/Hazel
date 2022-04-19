#pragma once
#include "Component.h"
#include "glm/glm.hpp"

namespace Hazel
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer() = default;
		SpriteRenderer(const glm::vec4& color) :m_Color(color) {}

		glm::vec4 GetColor() { return m_Color; }

	private:
		glm::vec4 m_Color;
	};
}