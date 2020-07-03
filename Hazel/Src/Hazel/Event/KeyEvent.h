#pragma once
#include "Event.h"

namespace Hazel
{
	class HAZEL_API KeyEvent : public Event
	{
	public:
	   inline int GetKeycode() const { return m_keycode;}
	protected:
		KeyEvent(int keycode): m_keycode(keycode){}
		int m_keycode;
	};

	class HAZEL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int keyRepeated) :KeyEvent(keycode), m_keyRepeated(keyRepeated) {}
		inline int GetRepeated() const { return m_keyRepeated; }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent:\n KeyCode : " << m_keycode << " KeyRepeated: " << m_keyRepeated;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	protected:
		int m_keyRepeated;
	};

	class HAZEL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) :KeyEvent(keycode) {}
		EVENT_CLASS_TYPE(KeyReleased)

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent:\n KeyCode : " << m_keycode;
			return ss.str();
		}
	
	protected:
	
	};


}