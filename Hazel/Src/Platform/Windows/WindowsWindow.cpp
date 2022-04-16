#include "hzpch.h"
#include "WindowsWindow.h"
#include "Hazel/Event/ApplicationEvent.h"
#include "Hazel/Event/KeyEvent.h"
#include "Hazel/Event/MouseEvent.h"
#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"


namespace Hazel
{
	static bool m_initialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}


	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
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
		
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);

		Renderer::Init();

		// glfw规定的回调函数里，不能传入m_Data的指针，所以只能通过glfw的API设置数据的指针
		// 下面函数会把m_Window传进去，然后又把m_Window作为lambda的参数输入进去
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.height = height;
			data.width = width;
			// 创建对应的Hazel Event，然后传入Window的callback函数里，以供外部调用
			WindowResizedEvent e(height, width);
			data.eventCallback(e);
		}
		);

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent e((float)xPos, (float)yPos);
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

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent e(key, 0);
					data.eventCallback(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent e(key, 1);
					data.eventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(key);
					data.eventCallback(e);
					break;
				}
				default:
					break;
			}
		
		}
		);

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int s)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent e(s);
			data.eventCallback(e);
		}
		);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.isVSync = enabled;
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffer();
	}

	void WindowsWindow::OnResized(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void* WindowsWindow::GetNativeWindow() const
	{
		return m_Window;
	}

	// only close windown, not terminate glfw
	void WindowsWindow::Shutdown()
	{
		if (m_initialized)
			glfwDestroyWindow(m_Window);
	}
}