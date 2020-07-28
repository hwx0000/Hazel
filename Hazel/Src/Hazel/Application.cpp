#include "hzpch.h"
#include "Application.h"
#include "GLFW/glfw3.h"
#include "Window.h"

namespace Hazel
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	void Application::OnEvent(Event& e)
	{
		//if (e.GetEventType() == EventType::WindowResize)
		//{
		//	LOG("WindoeResize Event Occures");
		//}
		LOG(e.ToString());
	}

	void Application::Run() 
	{
		std::cout << "Run Application" << std::endl;
		while (m_Running)
		{
			// Application����Ӧ��֪�����õ����ĸ�ƽ̨��window��Window��init��������Window::Create����
			// ���Դ�����window�󣬿���ֱ�ӵ�����loop��ʼ��Ⱦ
			m_Window->OnUpdate();
		}

		//LOG(w.ToString());
	}
}