#pragma once
#include "hzpch.h"
#include "Core.h"
#include "Event/Event.h"
#include "Renderer/GraphicsContext.h"

namespace Hazel
{
	struct HAZEL_API WindowProps
	{
	public:
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string& m_title = "Hazel Engine", unsigned int w = 1280, unsigned int h = 720)
			:title(m_title), width(w), height(h)
		{
		}
	};

	class HAZEL_API Window
	{
	public:
		// Window�Դ�һ���ص����������������glfw���յ���callback
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {};
		virtual int const GetWindowHeight() const = 0;
		virtual int const GetWindowWidth() const = 0;
		virtual bool IsVSync() const = 0;
		virtual void SetVSync(bool) = 0;
		virtual void OnUpdate() = 0;
		virtual void* GetNativeWindow() const = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		static Window* Create(const WindowProps& props = WindowProps());
		GraphicsContext* m_Context;
	};
}