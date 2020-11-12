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
		void OnImGuiRender() override; //��layer��layer stack�Ƴ���ʱ�����ô˺������൱��Shutdown����

		void Begin();// ��ԭ����OnUpdate�����ֽ����������
		void End();
	private:
		float m_Time = 0.0f;
	};
}