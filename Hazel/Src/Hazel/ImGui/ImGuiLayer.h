#pragma once
#include "Hazel/Core.h"
#include "Hazel/Layer.h"

namespace Hazel 
{
	HAZEL_API class ImGuiLayer : public Layer
	{
		ImGuiLayer(const std::string& name = "Layer");
		~ImGuiLayer();
		void OnAttach() override; //��layer��ӵ�layer stack��ʱ�����ô˺������൱��Init����
		void OnDettach() override; //��layer��layer stack�Ƴ���ʱ�����ô˺������൱��Shutdown����
		void OnEvent(Event&) override;
		void OnUpdate() override;
	};
}