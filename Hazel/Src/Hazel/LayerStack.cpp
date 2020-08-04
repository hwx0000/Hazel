#include "LayerStack.h"

LayerStack::LayerStack()
{
	curStackItr = stack.begin();
}

LayerStack::~LayerStack()
{
	for (Layer* i: stack)
	{
		delete i;
	}
}

// ��vectorģ��stack��vector[0]Ϊջ��
void LayerStack::PushLayer(Layer *layer)
{
	stack.emplace(stack.begin(), layer);
}

// overlayӦ�÷�����������Ҳ����ջ��
void LayerStack::PushOverlay(Layer *overlay)
{
	stack.emplace_back(overlay);
}

Layer* LayerStack::PopStack(Layer *)
{
	if (stack.size() > 0)
		stack.

	return nullptr;
}
