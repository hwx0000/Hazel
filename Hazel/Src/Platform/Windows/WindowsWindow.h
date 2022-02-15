#pragma once
#include "Core/Window.h"
#include <GLFW/glfw3.h>

namespace Hazel
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow() override;
		int const GetWindowHeight() const override { return m_Data.height; };
		int const GetWindowWidth() const override { return m_Data.width; };
		bool IsVSync() const override { return m_Data.isVSync; };
		void SetVSync(bool) override;
		void OnUpdate() override;
		void OnResized(int width, int height) override;
		void* GetNativeWindow() const override;
		inline void SetEventCallback(const EventCallbackFn& callback)override { m_Data.eventCallback = callback; };

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
			bool isVSync;
			EventCallbackFn eventCallback;
		};

		WindowData m_Data;
	};
}