#include "WindowsWindow.h"

static bool m_initialized = false;

void Hazel::WindowsWindows::Init()
{
}

void Hazel::WindowsWindows::SetVsync(int a)
{
	if (a)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);
}
