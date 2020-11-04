#pragma once
#include "Hazel/Core.h"
#include "Hazel/Layer.h"
#include "Hazel/Event/MouseEvent.h"
#include "Hazel/Event/KeyEvent.h"
#include "Hazel/Event/ApplicationEvent.h"

namespace Hazel 
{
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnAttach() override; //当layer添加到layer stack的时候会调用此函数，相当于Init函数
		void OnDettach() override; //当layer从layer stack移除的时候会调用此函数，相当于Shutdown函数
		void OnEvent(Event&) override;
		void OnUpdate() override;

	private:
		bool OnMouseCursorMoved(MouseMovedEvent&);
		bool OnMouseButtonPressed(MouseButtonPressedEvent&);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent&);
		bool OnMouseScrolled(MouseScrolledEvent&);
		bool OnKeyPressed(KeyPressedEvent&);
		bool OnKeyReleased(KeyReleasedEvent&);
		bool OnKeyTyped(KeyTypedEvent&);
		bool OnWindowResized(WindowResizedEvent&);
	private:
		float m_Time = 0.0f;
	};
}