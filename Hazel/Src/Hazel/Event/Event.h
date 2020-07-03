#pragma once
#include <string>
#include "Hazel/Core.h"
#include <sstream>

#define EVENT_CLASS_TYPE(type) \
static EventType GetStaticType() { return EventType::##type; }\
const EventType GetEventType() const override { return GetStaticType(); }\
const char* GetName() const override { return #type; }

namespace Hazel
{
	enum class HAZEL_API EventType
	{
		None = 0,
			WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
			AppTick, AppUpdate, AppRender,
			KeyPressed, KeyReleased,
			MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};


	class HAZEL_API Event
	{
	public:
		virtual const char* GetName() const = 0;
		virtual const EventType GetEventType() const = 0;

		virtual std::string ToString() const = 0;


	protected:
		bool m_handled = false;//用来标记这个事件是否被处理了
	};
}