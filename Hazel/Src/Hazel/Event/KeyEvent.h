#pragma once
#include "Event.h"

namespace Hazel
{
	class HAZEL_API KeyEvent : public Event
	{
	public:
	   inline int GetKeycode() const { return m_Keycode;}

	   EVENT_CLASS_GET_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
	protected:
		KeyEvent(int keycode)
			: m_Keycode(keycode){}
		int m_Keycode;
	};

	class HAZEL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int keyRepeated)
			:KeyEvent(keycode), m_KeyRepeated(keyRepeated) {}
		inline int GetRepeated() const { return m_KeyRepeated; }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent:\n KeyCode : " << m_Keycode << " KeyRepeated: " << m_KeyRepeated;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	protected:
		int m_KeyRepeated;
	};
	   
	class HAZEL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			:KeyEvent(keycode) {}
		EVENT_CLASS_TYPE(KeyReleased)

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent:\n KeyCode : " << m_Keycode;
			return ss.str();
		}
	
	protected:
	
	};


}