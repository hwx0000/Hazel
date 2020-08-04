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

// 用vector模拟stack，vector[0]为栈顶
void LayerStack::PushLayer(Layer *layer)
{
	stack.emplace(stack.begin(), layer);
}

// overlay应该放在数组的最后，也就是栈顶
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
