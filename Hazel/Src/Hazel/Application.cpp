#include "hzpch.h"
#include "Application.h"


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
		//LOG(w.ToString());
	}
}