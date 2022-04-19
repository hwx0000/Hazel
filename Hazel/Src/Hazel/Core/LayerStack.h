#pragma once
#include "Layer.h"

namespace Hazel
{
	// 这里用一个vector模拟了layer的栈，vector[0]代表栈底，vector[last]代表栈顶，存放了离摄像头最近的layer
	class HAZEL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		void PushLayer(std::shared_ptr<Layer>); // lay代表普通的layer, Overlay代表离屏幕最近的layer
		void PushOverlay(std::shared_ptr<Layer>);
		void PopOverlay(std::shared_ptr<Layer> overlay);
		std::shared_ptr<Layer> PopLayer();
		std::shared_ptr<Layer> GetLayer(uint32_t id) { return m_Stack[id]; }
		uint32_t GetLayerCnt() { return (uint32_t)m_Stack.size(); }

		std::vector<std::shared_ptr<Layer>>::iterator begin() {	return m_Stack.begin(); }
		std::vector<std::shared_ptr<Layer>>::iterator end() {	return m_Stack.end(); }
	private:
		std::vector<std::shared_ptr<Layer>>m_Stack;
		std::vector<std::shared_ptr<Layer>>::iterator curStackItr;
	};
}