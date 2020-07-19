#include "hzpch.h"
#include "Application.h"
#include "Platform/WindowsWindow.h"

namespace Hazel
{
	void Application::Run()
	{
		std::cout << "Run Application" << std::endl;
		WindowProps props;
		WindowsWindow w(props);
		while (true)
		{

		}
		//LOG(w.ToString());
	}
}