#pragma once
#include "Hazel/Timestep.h"
#include "Hazel/OrthographicCamera.h"
#include "Hazel/Event/Event.h"

namespace Hazel
{
	// 其实是个Camera的Wrapper
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float radio, float zoom);
		void OnUpdate(const Timestep&);
		void OnEvent(Event&);

		static OrthographicCameraController& Get() { return m_Instance; }
		static const OrthographicCameraController& Get() const { return m_Instance; }

	private:
		void OnZoomCamera(float scrollOffset);

	private:
		float m_ZoomLevel = 1.0f;
		float m_AspectRadio = 1.66667f;
		float m_ZoomSpeed = 120.0f;
		float m_RotateSpeed = 20.0f;
		bool m_Rotatable = true;
		OrthographicCamera m_Camera;
		OrthographicCameraController m_Instance;
	};

}