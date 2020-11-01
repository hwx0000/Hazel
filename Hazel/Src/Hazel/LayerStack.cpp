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
		for (Layer* layer : m_Stack)
			delete layer;
	}

	// ��vectorģ��m_Stack��vector[0]Ϊջ��
	void LayerStack::PushLayer(Layer *layer)
	{
		m_Stack.emplace(m_Stack.begin(), layer);
		layer->OnAttach();
	}

	// ��֤�����layer�������overlayӦ�÷�����������Ҳ����ջ��
	void LayerStack::PushOverlay(Layer *overlay)
	{
		m_Stack.emplace_back(overlay);
		overlay->OnAttach();
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

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Stack.begin(), m_Stack.end(), overlay);
		if (it != m_Stack.end())
			m_Stack.erase(it);
	}
}