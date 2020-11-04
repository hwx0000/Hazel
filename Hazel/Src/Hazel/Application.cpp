#include "hzpch.h"
#include "Application.h"
#include "Window.h"
#include "Event/MouseEvent.h"
#include "Event/ApplicationEvent.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HAZEL_ASSERT(!s_Instance, "Already Exists an application instance");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		//m_Window->SetEventCallback([](Event& e)->void
		//{
		//	if (e.GetEventType() == EventType::MouseScrolled)
		//	{
		//		MouseScrolledEvent ee = (MouseScrolledEvent&)e;
		//		LOG( "xOffset:{0} and yOffset:{1}", ee.GetXOffset(), ee.GetYOffset());
		//	}
		//}
		//);
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		//CORE_LOG("{0}", e);
		CORE_LOG(e.ToString());
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
		while (m_Running)
		{
			// 每帧开始Clear
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			// Application并不应该知道调用的是哪个平台的window，Window的init操作放在Window::Create里面
			// 所以创建完window后，可以直接调用其loop开始渲染
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
			// 每帧结束调用glSwapBuffer
			m_Window->OnUpdate();
		}

		//LOG(w.ToString());
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