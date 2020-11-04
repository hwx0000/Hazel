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
		void OnAttach() override; //��layer��ӵ�layer stack��ʱ�����ô˺������൱��Init����
		void OnDettach() override; //��layer��layer stack�Ƴ���ʱ�����ô˺������൱��Shutdown����
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