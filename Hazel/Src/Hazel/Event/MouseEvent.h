#pragma once
#include "Event.h"
#include <sstream>

namespace Hazel
{
	class MouseMovedEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_GET_CATEGORY(EventCategoryInput | EventCategoryMouse)


		std::string ToString() const override
		{
			std::stringstream a;
			a << "MouseMovedEvent: xOffset = " << GetXOffset() << ", yOffset = " << GetYOffset();
			return a.str();
		}

		inline float GetXOffset() const { return m_xOffset; }
		inline float GetYOffset() const { return m_yOffset; }
	private:
		float m_xOffset, m_yOffset;
	};

	class MouseButtonPressed : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseButtonPressed)
		EVENT_CLASS_GET_CATEGORY(EventCategoryInput | EventCategoryMouseButton)

		std::string ToString() const override
		{
			std::stringstream a;
			a << "MouseButtonPressed: xOffset = " << GetXOffset() << ", yOffset = " << GetYOffset();
			return a.str();
		}

		inline float GetXOffset() const { return m_xOffset; }
		inline float GetYOffset() const { return m_yOffset; }
	private:
		int keycode;
		float m_xOffset, m_yOffset;
	};
	
	class MouseButtonReleased : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseButtonReleased)
		EVENT_CLASS_GET_CATEGORY(EventCategoryInput | EventCategoryMouseButton)

		std::string ToString() const override
		{
			std::stringstream a;
			a << "MouseButtonReleased:  " << GetXOffset() << ", yOffset = " << GetYOffset();
			return a.str();
		}

		inline float GetXOffset() const { return m_xOffset; }
		inline float GetYOffset() const { return m_yOffset; }
	private:
		float m_xOffset, m_yOffset;
	};

	class MouseScrolled : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_GET_CATEGORY(EventCategoryInput | EventCategoryMouseButton)

		std::string ToString() const override
		{
			std::stringstream a;
			a << "MouseScrolled: xOffset = " << GetXOffset() << ", yOffset = " << GetYOffset();
			return a.str();
		}

		inline float GetXOffset() const { return m_xOffset; }
		inline float GetYOffset() const { return m_yOffset; }
	private:
		float m_xOffset, m_yOffset;
	};
}