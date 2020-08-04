#pragma once
#include "Layer.h"

// ������һ��vectorģ����layer��ջ��vector[0]����ջ�ף�vector[last]����ջ���������������ͷ�����layer
class HAZEL_API LayerStack 
{
public:
	LayerStack();
	~LayerStack();
	void PushLayer(Layer*); // lay������ͨ��layer, Overlay��������Ļ�����layer
	void PushOverlay(Layer*);
	Layer* PopStack(Layer*);

private:
	std::vector<Layer*>stack;
	std::vector<Layer*>::iterator curStackItr;
};