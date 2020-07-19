#pragma once
#include "Core.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"
#include "Platform/WindowsWindow.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application()
		{

		}

		void Run();
	private:
		std::unique_ptr<Window>m_Window;
	};

	//Application* CreateApplication();
}