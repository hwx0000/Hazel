#pragma once
#include "Hazel.h"

class SandboxApp : public Hazel::Application
{
public:
	SandboxApp();
	virtual void Run() override;
	~SandboxApp() {};
private:
	Timestep m_Timestep;
};