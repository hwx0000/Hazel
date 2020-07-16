#pragma once
#include "Hazel/Window.h"
#include "GLFW/glfw3.h"

namespace Hazel
{
	class WindowsWindows : public Window
	{
	public:
		~WindowsWindows() override {};
		void Init();
		float const& GetWindowHeight() const override { return m_Data.height; };
		float const& GetWindowWidth() const override { return m_Data.width; };
		int GetVsync() const override { return m_Data.isVsync; };
		void SetVsync(int a) override;
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