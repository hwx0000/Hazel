#pragma once
#include "Component.h"
#include "glm/glm.hpp"

namespace Hazel
{
	class Transform : public Component
	{
	public:
		Transform() = default;

		glm::mat4 GetTransformMat();
		glm::vec3 Translation = { 0, 0, 0 };
		glm::vec3 Rotation = { 0, 0, 0 };
		glm::vec3 Scale = { 1, 1, 1 };
	};
}