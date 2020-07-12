#pragma once
#include "Event.h"
#include <sstream>

namespace Hazel
{
	class MouseMovedEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseMoved)

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