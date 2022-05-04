#include "hzpch.h"
#include "CameraComponent.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Hazel
{
	CameraComponent::CameraComponent(float left, float right, float bottom, float top)
		: m_Projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
	{
	}
}
