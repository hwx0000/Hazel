#include "hzpch.h"
#include "Application.h"

namespace Hazel
{
	void Application::Run()
	{
		std::cout << "Run Application" << std::endl;
		WindowCloseEvent e(200, 400);
		LOG( e.ToString());
	}
}