#include "hzpch.h"
#include "EditorCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Hazel
{
	EditorCamera::EditorCamera(ProjectionType type, float leftOrFov, float rightOrAspect, float bottomOrZNear, float topOrZFar)
	{
		m_ZoomLevel = topOrZFar;
		m_AspectRatio = rightOrAspect / m_ZoomLevel;

		if (type == ProjectionType::Orthographic)
		{
			m_ProjectionMatrix = glm::ortho(leftOrFov, rightOrAspect, bottomOrZNear, topOrZFar, -1.0f, 1.0f);
			m_ViewMatrix = glm::mat4(1.0f);
		}
		else if(type == ProjectionType::Perspective)
		{
			m_ViewMatrix = glm::lookAt(m_Position, m_Position + GetLocalForward(), GetLocalUp());
			m_ProjectionMatrix = glm::perspective(glm::radians(leftOrFov), rightOrAspect, bottomOrZNear, topOrZFar);
		}

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void EditorCamera::RecalculateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + GetLocalForward(), GetLocalUp());
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void EditorCamera::OnResize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		if (m_Type == ProjectionType::Orthographic)
		{
			// 里面会调用glm::ortho(float left, float right, float bottom, float top)函数
			// 根据这段代码可知, camera看到的区域高度不会随着窗口大小而改变
			// 而是会随着鼠标滚动改变zoom值而变化
			SetProjectionMatrixOrtho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		}
		else if (m_Type == ProjectionType::Perspective)
			RecalculateViewMatrix();
	}

	void EditorCamera::SetPosition(const glm::vec3& position)
	{
		if (m_Position != position)
		{
			m_Position = position;
			RecalculateViewMatrix();
		}
	}

	void EditorCamera::SetRotation(glm::quat rotation)
	{
		if (m_Rotation != rotation)
		{
			m_Rotation = rotation;
			RecalculateViewMatrix();
		}
	}

	void EditorCamera::SetProjectionMatrixOrtho(float left, float right, float bottom, float top)
	{
		HAZEL_ASSERT(bool(m_Type == ProjectionType::Orthographic), "The camera must be orthographic!");
			
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);

		// Update VP mat4
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void EditorCamera::SetProjectionMatrixPersp(float fov, float aspect, float zNear, float zFar)
	{
		HAZEL_ASSERT(bool(m_Type == ProjectionType::Perspective), "The camera must be perspective!")

		m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect, zNear, zFar);

		// Update VP mat4
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}

