#pragma once
#include "Layer.h"

namespace Hazel
{
	// ������һ��vectorģ����layer��ջ��vector[0]����ջ�ף�vector[last]����ջ���������������ͷ�����layer
	class HAZEL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		void PushLayer(Layer*); // lay������ͨ��layer, Overlay��������Ļ�����layer
		void PushOverlay(Layer*);
		Layer* PopLayer();

		std::vector<Layer*>::iterator begin() {	return m_Stack.begin(); }
		std::vector<Layer*>::iterator end() {	return m_Stack.end(); }
	private:
		std::vector<Layer*>m_Stack;
		std::vector<Layer*>::iterator curStackItr;
	};
}