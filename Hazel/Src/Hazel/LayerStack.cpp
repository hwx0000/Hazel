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

	// ��vectorģ��m_Stack��vector[0]Ϊջ��
	void LayerStack::PushLayer(Layer *layer)
	{
		m_Stack.emplace(m_Stack.begin(), layer);
	}

	// ��֤�����layer�������overlayӦ�÷�����������Ҳ����ջ��
	void LayerStack::PushOverlay(Layer *overlay)
	{
		m_Stack.emplace_back(overlay);
	}

	// pop����ĵ�һ��Ԫ��
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