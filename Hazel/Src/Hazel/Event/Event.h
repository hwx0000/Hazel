#pragma once
#include "hzpch.h"
#include "Hazel/Core.h"

#define EVENT_CLASS_TYPE(type) \
static EventType GetStaticType() { return EventType::##type; }\
const EventType GetEventType() const override { return GetStaticType(); }\
const char* GetName() const override { return #type; }

#define EVENT_CLASS_GET_CATEGORY(category) int GetCategoryFlag() const override { return category;} 

namespace Hazel
{
	// �¼�����ϸ����
	enum class HAZEL_API EventType
	{
		None = 0,
		WindowClose, WindowResized, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// �¼��Ĵ�������
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4),
	};


	class HAZEL_API Event
	{
	public:
		friend class EventDispatcher;
		virtual const char* GetName() const = 0;
		virtual const EventType GetEventType() const = 0;
		virtual int GetCategoryFlag() const = 0;
		virtual std::string ToString() const { return GetName(); }
		inline bool IsInCategory(EventCategory type) 
		{
			return GetCategoryFlag() & type;
		}

	protected:
		bool m_Handled = false;//�����������¼��Ƿ񱻴�����
	};

	// ���յ�Eventʱ��������Ӧ��EventDispatcher
	class HAZEL_API EventDispatcher 
	{
		template<typename T>
		using EventHandler = std::function<bool(T&)>;//EventHandler�洢��һ������Ϊ�������͵����ã�����ֵΪbool�ĺ���ָ��
	public:
		EventDispatcher(Event& event):
			m_Event(event){}

		// Tָ�����¼�����, ������������û��GetStaticType�ᱨ��
		template<typename T>
		void Dispatch(EventHandler<T> handler)
		{
			if (m_Event.m_Handled)
				return;

			if (m_Event.GetEventType() == T::GetStaticType()) 
			{
				m_Event.m_Handled = handler(*(T*)&m_Event); //ʹ��(T*)��m_Eventת���������¼���ָ������
				m_Event.m_Handled = true;// Temporary: ���ڲ���ֱ�Ӷ�Ӧ��Handler�ﶼ����true
			}
		}

	private:
		Event& m_Event;//���������ã���������Event��ʵ������ΪEvent���д��麯��
	};
}