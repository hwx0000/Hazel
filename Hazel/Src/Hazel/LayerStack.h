#pragma once
#include "Layer.h"

// 这里用一个vector模拟了layer的栈，vector[0]代表栈底，vector[last]代表栈顶，存放了离摄像头最近的layer
class HAZEL_API LayerStack 
{
public:
	LayerStack();
	~LayerStack();
	void PushLayer(Layer*); // lay代表普通的layer, Overlay代表离屏幕最近的layer
	void PushOverlay(Layer*);
	Layer* PopStack(Layer*);

private:
	std::vector<Layer*>stack;
	std::vector<Layer*>::iterator curStackItr;
};