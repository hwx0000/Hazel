#pragma once
#include "Hazel/Window.h"
#include "GLFW/glfw3.h"

namespace Hazel
{
	class WindowsWindows : public Window
	{
	public:
		WindowsWindows(const WindowProps& props);
		~WindowsWindows() override;
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