#pragma once
#include "Component.h"
#include "glm/glm.hpp"

namespace Hazel
{
	class CameraComponent : public Component
	{
	public:
		CameraComponent(float left, float right, float bottom, float top);

		glm::mat4 GetProjectionMatrix() { return m_Projection; }
		glm::mat4 GetProjectionMatrix() const { return m_Projection; }

	private:
		glm::mat4 m_Projection;// Camera的View矩阵由对应的Transform来记录
	};
}