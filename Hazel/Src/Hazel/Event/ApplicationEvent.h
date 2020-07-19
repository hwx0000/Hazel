#pragma once
#include "Event.h"

// Windows和APP相关的Event都在这里处理
namespace Hazel
{
	class HAZEL_API WindowCloseEvent :public Event
	{
	public:
		WindowCloseEvent(float height, float width):
			m_Height(height), m_Width(width) {}
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_GET_CATEGORY(EventCategoryApplication)
	
		
		std::string ToString() const override
		{
			std::stringstream a;
			a << "Window Close";
			return a.str();
		}
	protected:
		float m_Height, m_Width;
	};

	class HAZEL_API  WindowResizeEvent :public Event
	{
	public:
		WindowResizeEvent(float height, float width):m_height(height), m_width(width) {}
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_GET_CATEGORY(EventCategoryApplication)

		std::string ToString() const override
		{
			std::stringstream a;
			a << "Window Resize: width = " << m_width << ", height = " << m_height;
			return a.str();
		}

	protected:
		float m_height, m_width;
	};

	class HAZEL_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_GET_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_GET_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_GET_CATEGORY(EventCategoryApplication)
	};

}