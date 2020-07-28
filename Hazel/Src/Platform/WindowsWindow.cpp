#include "hzpch.h"
#include "WindowsWindow.h"
#include "Hazel/Event/ApplicationEvent.h"
#include "Hazel/Event/KeyEvent.h"
#include "Hazel/Event/MouseEvent.h"

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

		glfwSetWindowUserPointer(m_Window, &m_Data);
		// glfw�涨�Ļص���������ܴ���m_Data��ָ�룬����ֻ��ͨ��glfw��API�������ݵ�ָ��
		// ���溯�����m_Window����ȥ��Ȼ���ְ�m_Window��Ϊlambda�Ĳ��������ȥ
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.height = height;
			data.width = width;
			// ������Ӧ��Hazel Event��Ȼ����Window��callback������Թ��ⲿ����
			WindowResizeEvent e(height, width);
			data.eventCallback(e);
		}
		);



		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent closeEvent;
			data.eventCallback(closeEvent);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.eventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			switch (action)
			{
				case GLFW_PRESS:
				{
					WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
					MouseButtonPressedEvent e(button);
					data.eventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
					MouseButtonReleasedEvent e(button);
					data.eventCallback(e);
					break;
				}
				default:
					break;
			}
		});

		SetVSync(true);
	}

	void Hazel::WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.isVSync = enabled;
	}

	void Hazel::WindowsWindow::OnUpdate()
	{
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
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