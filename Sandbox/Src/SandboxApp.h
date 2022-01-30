#pragma once
#include "Hazel.h"
#include "ExampleLayer.h"

class Sandbox : public Hazel::Application
{
public:
	Sandbox();
	//{
	//	m_LayerStack.PushLayer(new ExampleLayer());
	//};
	virtual void Run() override;
	~Sandbox() {};
private:
};