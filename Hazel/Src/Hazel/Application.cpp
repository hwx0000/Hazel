#include "hzpch.h"
#include "Application.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Event/MouseEvent.h"
#include "Event/ApplicationEvent.h"
#include "glad/glad.h"

namespace Hazel
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		unsigned int buffer;
		glGenBuffers(1, &buffer);
		
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
			// Application����Ӧ��֪�����õ����ĸ�ƽ̨��window��Window��init��������Window::Create����
			// ���Դ�����window�󣬿���ֱ�ӵ�����loop��ʼ��Ⱦ
			m_Window->OnUpdate();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
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