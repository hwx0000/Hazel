#pragma once
#include "Hazel/Window.h"
#include "GLFW/glfw3.h"

namespace Hazel
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow() override;
		void Init(const WindowProps& props);
		float const& GetWindowHeight() const override { return m_Data.height; };
		float const& GetWindowWidth() const override { return m_Data.width; };
		bool IsVsync() const override { return m_Data.isVsync; };
		void SetVsync(bool) override;

	private:
		GLFWwindow *m_Window;
		struct WindowData
		{
			std::string title;
			unsigned int height, width;
			bool isVsync;
		};
		WindowData m_Data;
	};
}