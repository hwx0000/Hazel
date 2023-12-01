#include "hzpch.h"
#include "CameraComponent.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Hazel
{
	CameraComponent::CameraComponent()
	{
		m_OrthographicNear = -1.0f;
		m_OrthographicFar = 1.0f;
		RecalculateProjectionMat();
		RecalculateViewMatrix();
	}

	void CameraComponent::SetAspectRatio(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		RecalculateProjectionMat();
	}

	void CameraComponent::RecalculateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + GetLocalForward(), GetLocalUp());
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void CameraComponent::RecalculateProjectionMat()
	{
		if (m_ProjectionType == ProjectionType::Orthographic)
		{
			float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
			float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
			float orthoBottom = -m_OrthographicSize * 0.5f;
			float orthoTop = m_OrthographicSize * 0.5f;
			m_ProjectionMatrix = glm::ortho(orthoLeft, orthoRight,
				orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
		}
		else
		{
			m_ProjectionMatrix = glm::perspective(glm::radians(m_PerspectiveFOV), m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
		}
	}
}
