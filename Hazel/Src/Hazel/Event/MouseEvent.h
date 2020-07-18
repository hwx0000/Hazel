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


	class MouseButtonEvent : public Event
	{
	public:
		EVENT_CLASS_GET_CATEGORY(EventCategoryInput | EventCategoryMouseButton)
		MouseButtonEvent(int button):
			m_Button(button){}
		virtual ~MouseButtonEvent() {}
		inline int GetMouseButton() const { return m_Button; };

	protected:
		int m_Button;
	};

	class MouseButtonPressed : public MouseButtonEvent
	{
	public:
		MouseButtonPressed(int button, float xOffset, float yOffset) :
			MouseButtonEvent(button), m_XOffset(xOffset), m_YOffset(yOffset) {}
		EVENT_CLASS_TYPE(MouseButtonPressed)

		std::string ToString() const override
		{
			std::stringstream a;
			a << "MouseButtonPressed: xOffset = " << GetXOffset() << ", yOffset = " << GetYOffset();
			return a.str();
		}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }
	private:
		float m_XOffset, m_YOffset;
	};
	
	class MouseButtonReleased : public MouseButtonEvent
	{
	public:
		MouseButtonReleased(int button, float xOffset, float yOffset) :
			MouseButtonEvent(button), m_XOffset(xOffset), m_YOffset(yOffset) {}
		EVENT_CLASS_TYPE(MouseButtonReleased)

		std::string ToString() const override
		{
			std::stringstream a;
			a << "MouseButtonReleased:  " << GetXOffset() << ", yOffset = " << GetYOffset();
			return a.str();
		}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }
	private:
		float m_XOffset, m_YOffset;
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