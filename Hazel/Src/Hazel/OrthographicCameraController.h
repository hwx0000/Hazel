#pragma once
#include "Core/Timestep.h"
#include "OrthographicCamera.h"
#include "Event/Event.h"

namespace Hazel
{
	// 其实是个Camera的Wrapper
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float radio, float zoom);
		void OnUpdate(const Timestep&);
		void OnEvent(Event&);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

	private:
		void OnZoomCamera(float scrollOffset);

	private:
		float m_ZoomLevel = 0.8f;
		float m_ZoomSpeed = 120.0f;
		float m_AspectRadio = 1.77778f;
		float m_RotateSpeed = 20.0f;
		bool m_Rotatable = true;
		OrthographicCamera m_Camera;
	};

}