#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Event/ApplicationEvent.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		void PushLayer(Layer* layer);
		Layer* PopLayer();
	protected:
		LayerStack m_LayerStack;
		std::unique_ptr<Window>m_Window;
		bool m_Running = true;
	};

	Application* CreateApplication();
}