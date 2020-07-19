#include "hzpch.h"
#include "WindowsWindow.h"

namespace Hazel
{
	static bool m_initialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	Hazel::WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	Hazel::WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void Hazel::WindowsWindow::Init(const WindowProps& props)
	{
		if (!m_initialized)
		{
			m_initialized = true;
			int r = glfwInit();
			HAZEL_ASSERT(r, "Failed to init glfw!")
		}

		m_Data.title = props.title;
		m_Data.height = props.height;
		m_Data.width = props.width;
		m_Window = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title.c_str(), NULL, NULL);
		HAZEL_ASSERT(m_Window, "Failed to create Windows Window!");
		glfwMakeContextCurrent(m_Window);
		//TODO: glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVsync(true);
	}

	void Hazel::WindowsWindow::SetVsync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.isVsync = enabled;
	}

	// only close windown, not terminate glfw
	void WindowsWindow::Shutdown()
	{
		if (m_initialized)
		{
			glfwDestroyWindow(m_Window);
		}
	}
}