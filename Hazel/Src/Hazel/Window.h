#pragma once
#include "hzpch.h"
#include "Core.h"
#include "Event/Event.h"

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
		using EventCallbackFn = std::function<void(Event&)>();
		virtual ~Window() {};
		virtual float const& GetWindowHeight() const = 0;
		virtual float const& GetWindowWidth() const = 0;
		virtual bool IsVsync() const = 0;
		virtual void SetVsync(bool) = 0;
		virtual void OnUpdate() = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}