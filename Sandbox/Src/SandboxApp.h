#pragma once
#include "Hazel.h"

// 注意, 这里的SandboxApp只可以创建对应的Layer, 然后加入到Application的
// m_LayerStack里, 具体调用的函数在Application.cpp的Run函数里
// Run函数是不会暴露给子类去override的
class SandboxApp : public Hazel::Application
{
public:
	SandboxApp();
	~SandboxApp() {};
};