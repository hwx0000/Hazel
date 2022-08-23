#include "hzpch.h"
#include "CameraComponent.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Hazel
{
	// 这里的right和top应该是分别与left和bottom互为相反数
	CameraComponent::CameraComponent()
	{
		m_OrthographicNear = -1.0f;
		m_OrthographicFar = 1.0f;
		RecalculateProjectionMat();
	}

	void CameraComponent::SetAspectRatio(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		RecalculateProjectionMat();
	}

	void CameraComponent::RecalculateProjectionMat()
	{
		if (m_ProjectionType == ProjectionType::Orthographic)
		{
			float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
			float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
			float orthoBottom = -m_OrthographicSize * 0.5f;
			float orthoTop = m_OrthographicSize * 0.5f;
			m_Projection = glm::ortho(orthoLeft, orthoRight,
				orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
		}
		else
		{
			m_Projection = glm::perspective(glm::radians(m_PerspectiveFOV), m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
		}
	}
}
