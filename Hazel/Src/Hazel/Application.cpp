#include "hzpch.h"
#include "Application.h"
#include "GLFW/glfw3.h"
#include "Window.h"

namespace Hazel
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		//m_Window = std::make_unique<Window>(Window::Create());
	}

	void Application::Run() 
	{
		std::cout << "Run Application" << std::endl;
		while (m_Running)
		{
			// Application并不应该知道调用的是哪个平台的window，Window的init操作放在Window::Create里面
			// 所以创建完window后，可以直接调用其loop开始渲染
			m_Window->OnUpdate();
		}

		//LOG(w.ToString());
	}
}