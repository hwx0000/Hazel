#pragma once
#include "Core/Timestep.h"
#include "EditorCamera.h"
#include "Event/Event.h"

namespace Hazel
{
	// 其实是个Camera的Wrapper
	class EditorCameraController
	{
	public:
		EditorCameraController(float radio, float zoom);
		EditorCameraController(float fov, float aspect, float zNear, float zFar);
		void OnUpdate(const Timestep&);
		void OnEvent(Event&);

		EditorCamera& GetCamera() { return m_Camera; }
		const EditorCamera& GetCamera() const { return m_Camera; }

	private:
		void OnZoomCamera(float scrollOffset);
		void RotatePerspectiveCamera(glm::quat& outQ, float deltaX, float deltaY);

	private:
		float m_ZoomLevel = 0.8f;
		float m_ZoomSpeed = 120.0f;
		float m_AspectRadio = 1.77778f;
		float m_RotateSpeed = 20.0f;
		bool m_Rotatable = true;
		glm::vec2 m_LastMousePos = { -1, -1 };
		glm::vec2 m_DeltaPos = { 0, 0 };// Used only for perspective camera
		EditorCamera m_Camera;
	};
}