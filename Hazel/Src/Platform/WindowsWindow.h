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
		float const& GetWindowHeight() const override { return m_Data.height; };
		float const& GetWindowWidth() const override { return m_Data.width; };
		bool IsVsync() const override { return m_Data.isVsync; };
		void SetVsync(bool) override;
		void OnUpdate()override;

	private:
		virtual void Shutdown();
		virtual void Init(const WindowProps& props);
	private:
		GLFWwindow *m_Window;

		// WindowData与WindowProp不同，这个创建这个类是为了方便和glfw交互
		struct WindowData
		{
			std::string title;
			unsigned int height, width;
			bool isVsync;
			//TODO: Add Event Callback
		};
		WindowData m_Data;
	};
}