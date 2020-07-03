#pragma once
#include "Event.h"

// Windows和APP相关的Event都在这里处理

namespace Hazel
{
	class HAZEL_API WindowCloseEvent :public Event
	{
	public:
		WindowCloseEvent(float height, float width):m_height(height), m_width(width) {}

		EVENT_CLASS_TYPE(WindowClose)
	protected:
		float m_height, m_width;
	};

	class HAZEL_API  WindowResizeEvent :public Event
	{
	public:
		WindowResizeEvent(float height, float width):m_height(height), m_width(width) {}
		EVENT_CLASS_TYPE(WindowResize)

	protected:
		float m_height, m_width;
	};

	class HAZEL_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
	};

	class HAZEL_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
	};

	class HAZEL_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
	};

}