#pragma once
#include "Core/Core.h"
#include "Core/Layer.h"
#include "Event/MouseEvent.h"
#include "Event/KeyEvent.h"
#include "Event/ApplicationEvent.h"

namespace Hazel 
{
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnAttach() override; //当layer添加到layer stack的时候会调用此函数，相当于Init函数
		void OnDettach() override; //当layer从layer stack移除的时候会调用此函数，相当于Shutdown函数
		void OnImGuiRender() override; //当layer从layer stack移除的时候会调用此函数，相当于Shutdown函数
		void OnEvent(Event&) override;

		void Begin();// 把原来的OnUpdate函数分解成了两部分
		void End();
	private:
		float m_Time = 0.0f;
	};
}