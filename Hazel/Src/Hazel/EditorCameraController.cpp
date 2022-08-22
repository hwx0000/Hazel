#include "hzpch.h"
#include "EditorCameraController.h"
#include "Core/Input.h"
#include "Core/KeyCode.h"
#include "Event/MouseEvent.h"
#include "Event/KeyEvent.h"

namespace Hazel
{
	EditorCameraController::EditorCameraController(float radio, float zoom):
		m_Camera(-radio * zoom, radio * zoom, -zoom, zoom)
	{

	}

	void EditorCameraController::OnUpdate(const Timestep & ts)
	{
		auto m_CameraPosition = m_Camera.GetPosition();
		auto m_CameraRotation = m_Camera.GetRotation();
		float m_CameraMoveSpeed = 1.0f;
		float m_CameraRotationSpeed = 10.0f;

		if (Input::IsMouseButtonPressed(2))
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
					m_CameraPosition -= m_Camera.GetLocalRight() * (float)ts;
				else if (Input::IsKeyPressed(HZ_KEY_D))
					m_CameraPosition += m_Camera.GetLocalRight() * (float)ts;

				if (Input::IsKeyPressed(HZ_KEY_W))
					m_CameraPosition += m_Camera.GetLocalForward() * (float)ts;
				else if (Input::IsKeyPressed(HZ_KEY_S))
					m_CameraPosition -= m_Camera.GetLocalForward() * (float)ts;
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
	}

	void EditorCameraController::OnZoomCamera(float scrollOffset)
	{
		m_ZoomLevel -= scrollOffset;
		m_ZoomLevel = std::clamp(m_ZoomLevel, 0.15f, 3.0f);
		m_Camera.SetProjectionMatrix(-m_AspectRadio * m_ZoomLevel, m_AspectRadio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}
}
