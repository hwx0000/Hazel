#pragma once
#include "Hazel/Core.h"
#include "Hazel/Layer.h"

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
		float m_Time = 0.0f;
	};
}