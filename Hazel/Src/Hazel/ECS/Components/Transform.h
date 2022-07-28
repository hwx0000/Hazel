#pragma once
#include "Component.h"
#include "glm/glm.hpp"

namespace Hazel
{
	class Transform : public Component
	{
	public:
		Transform() = default;

		operator glm::mat4&() { return transform; }

	private:
		glm::mat4 transform = glm::mat4(1.0f);
	};
}