#include "hzpch.h"
#include "EditorCameraController.h"
#include "Core/Input.h"
#include "Core/KeyCode.h"
#include "Event/MouseEvent.h"
#include "Event/KeyEvent.h"

namespace Hazel
{
	EditorCameraController::EditorCameraController(float radio, float zoom):
		m_Camera(EditorCamera::ProjectionType::Orthographic, -radio * zoom, radio * zoom, -zoom, zoom)
	{

	}

	EditorCameraController::EditorCameraController(float fov, float aspect, float zNear, float zFar) :
		m_Camera(EditorCamera::ProjectionType::Perspective, fov, aspect, zNear, zFar)
	{

	}

	void EditorCameraController::OnUpdate(const Timestep & ts)
	{
		auto m_CameraPosition = m_Camera.GetPosition();
		auto m_CameraRotation = m_Camera.GetRotation();
		float m_CameraMoveSpeed = 1.0f;
		float m_CameraRotationSpeed = 10.0f;

		if (Input::IsMouseButtonPressed(1))
		{
			if (m_Camera.IsOrthographicCamera())
			{
				if (Input::IsKeyPressed(HZ_KEY_A))
					m_CameraPosition.x -= m_CameraMoveSpeed * ts;
				else if (Input::IsKeyPressed(HZ_KEY_D))
					m_CameraPosition.x += m_CameraMoveSpeed * ts;

				if (Input::IsKeyPressed(HZ_KEY_W))
					m_CameraPosition.y += m_CameraMoveSpeed * ts;
				else if (Input::IsKeyPressed(HZ_KEY_S))
					m_CameraPosition.y -= m_CameraMoveSpeed * ts;
			}
			else if (m_Camera.IsProjectiveCamera())
			{
				if (Input::IsKeyPressed(HZ_KEY_A))
					m_CameraPosition += m_Camera.GetLocalRight() * (float)ts;
				else if (Input::IsKeyPressed(HZ_KEY_D))
					m_CameraPosition -= m_Camera.GetLocalRight() * (float)ts;
				else if (Input::IsKeyPressed(HZ_KEY_W))
					m_CameraPosition += m_Camera.GetLocalForward() * (float)ts;
				else if (Input::IsKeyPressed(HZ_KEY_S))
					m_CameraPosition -= m_Camera.GetLocalForward() * (float)ts;
				else if (m_DeltaPos.x != 0 || m_DeltaPos.y != 0)
				  RotatePerspectiveCamera(m_CameraRotation, m_DeltaPos.x * ts, m_DeltaPos.y * ts);

				m_DeltaPos = { 0, 0 };
			}
		}

		if (m_Rotatable)
		{
			if (m_Camera.IsOrthographicCamera())
			{
				// 由于是2D的Camera, 用一个绕Z轴的角度表示相机旋转即可
				if (Input::IsKeyPressed(HZ_KEY_LEFT))
					m_CameraRotation = glm::rotate(m_CameraRotation, m_CameraRotationSpeed * ts, { 0, 0, 1 });
				if (Input::IsKeyPressed(HZ_KEY_RIGHT))
					m_CameraRotation = glm::rotate(m_CameraRotation, -m_CameraRotationSpeed * ts, { 0, 0, 1 });
			}
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
	}

	void EditorCameraController::OnEvent(Event &e)
	{
		if (e.GetEventType() == Hazel::EventType::MouseScrolled)
		{
			MouseScrolledEvent* ep = dynamic_cast<Hazel::MouseScrolledEvent*>(&e);
			OnZoomCamera(ep->GetYOffset());
		}

		if (e.GetEventType() == Hazel::EventType::MouseButtonReleased)
		{
			MouseButtonReleasedEvent* ep = dynamic_cast<Hazel::MouseButtonReleasedEvent*>(&e);
			if (ep->GetMouseButton() == 1)
				m_LastMousePos = { -1, -1 };
		}

		if (m_Camera.IsProjectiveCamera())
		{
			if (Input::IsMouseButtonPressed(1))
			{
				if (e.GetEventType() == Hazel::EventType::MouseMoved)
				{
					MouseMovedEvent* ep = dynamic_cast<Hazel::MouseMovedEvent*>(&e);

					if (m_LastMousePos != glm::vec2(-1, -1))
					{
						m_DeltaPos.x = ep->GetXPos() - m_LastMousePos.x;
						m_DeltaPos.y = ep->GetYPos() - m_LastMousePos.y;
					}

					m_LastMousePos.x = ep->GetXPos();
					m_LastMousePos.y = ep->GetYPos();
				}
			}
		}
	}

	void EditorCameraController::OnZoomCamera(float scrollOffset)
	{
		if (m_Camera.IsOrthographicCamera())
		{
			m_ZoomLevel -= scrollOffset;
			m_ZoomLevel = std::clamp(m_ZoomLevel, 0.15f, 3.0f);
			m_Camera.SetProjectionMatrix(-m_AspectRadio * m_ZoomLevel, m_AspectRadio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		}
	}

	void EditorCameraController::RotatePerspectiveCamera(glm::quat& outQ, float deltaX, float deltaY)
	{
		if (deltaX)
		{
			auto localUp = m_Camera.GetLocalUp();
			auto deltaM = glm::rotate(glm::mat4(1.0f), deltaX, localUp);
			outQ = outQ * glm::toQuat(deltaM);
		}

		if (deltaY)
		{
			auto localRight = m_Camera.GetLocalRight();
			auto deltaM = glm::rotate(glm::mat4(1.0f), deltaY, localRight);
			outQ = outQ * glm::toQuat(deltaM);
		}
	}
}
