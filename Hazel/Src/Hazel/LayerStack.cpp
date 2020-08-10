#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel
{
	LayerStack::LayerStack()
	{
		curStackItr = m_Stack.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* i : m_Stack)
		{
			delete i;
		}
	}

	// 用vector模拟m_Stack，vector[0]为栈顶
	void LayerStack::PushLayer(Layer *layer)
	{
		m_Stack.emplace(m_Stack.begin(), layer);
	}

	// 保证加入的layer放在最后，overlay应该放在数组的最后，也就是栈顶
	void LayerStack::PushOverlay(Layer *overlay)
	{
		m_Stack.emplace_back(overlay);
	}

	// pop数组的第一个元素
	Layer* LayerStack::PopLayer()
	{
		if (m_Stack.size() > 0)
		{
			Layer* top = m_Stack[0];
			m_Stack.erase(m_Stack.begin(), m_Stack.begin() + 1);
			return top;
		}
		else
			return nullptr;
	}
}