#include "hzpch.h"
#include "Application.h"
#include "Window.h"
#include "Event/MouseEvent.h"
#include "Event/ApplicationEvent.h"
#include "Input.h"
#include "Renderer/Buffer.h"
#include "Hazel/Renderer/RenderCommand.h"
#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/KeyCode.h"

namespace Hazel
{
	Hazel::Application* Hazel::Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		for (Layer* layer : m_LayerStack)
		{
			layer->OnEvent(e);
		}
	}


	void Application::Run() 
	{
		std::cout << "Run Application" << std::endl;
	}

	bool Application::OnWindowClose(WindowCloseEvent &e)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer * layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	Layer* Application::PopLayer()
	{
		return m_LayerStack.PopLayer();
	}
}