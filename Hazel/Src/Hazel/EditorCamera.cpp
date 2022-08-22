#include "hzpch.h"
#include "EditorCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Hazel
{
	EditorCamera::EditorCamera(ProjectionType type, float leftOrFov, float rightOrAspect, float bottomOrZNear, float topOrZFar)
	{
		//m_Camera(-radio * zoom, radio * zoom, -zoom, zoom)
		m_ZoomLevel = topOrZFar;
		m_AspectRatio = rightOrAspect / m_ZoomLevel;

		if (type == ProjectionType::Orthographic)
		{
			m_ProjectionMatrix = glm::ortho(leftOrFov, rightOrAspect, bottomOrZNear, topOrZFar, -1.0f, 1.0f);
			m_ViewMatrix = glm::mat4(1.0f);
		}
		else if(type == ProjectionType::Perspective)
		{
			m_ProjectionMatrix = glm::perspective(leftOrFov, rightOrAspect, bottomOrZNear, topOrZFar);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(m_Rotation);
			m_ViewMatrix = glm::inverse(transform);
		}

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void EditorCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(m_Rotation);
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void EditorCamera::OnResize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		// 里面会调用glm::ortho(float left, float right, float bottom, float top)函数
		// 根据这段代码可知, camera看到的区域高度不会随着窗口大小而改变
		// 而是会随着鼠标滚动改变zoom值而变化
		SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	void EditorCamera::SetProjectionMatrix(float leftOrFov, float rightOrAspect, float bottomOrZNear, float topOrZFar)
	{
		if(m_Type == ProjectionType::Orthographic)
			m_ProjectionMatrix = glm::ortho(leftOrFov, rightOrAspect, bottomOrZNear, topOrZFar, -1.0f, 1.0f);
		else if (m_Type == ProjectionType::Perspective)
			m_ProjectionMatrix = glm::perspective(leftOrFov, rightOrAspect, bottomOrZNear, topOrZFar);

		// Update VP mat4
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}

