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
		void OnAttach() override; //当layer添加到layer stack的时候会调用此函数，相当于Init函数
		void OnDettach() override; //当layer从layer stack移除的时候会调用此函数，相当于Shutdown函数
		void OnEvent(Event&) override;
		void OnUpdate() override;
	private:
		float m_Time = 0.0f;
	};
}