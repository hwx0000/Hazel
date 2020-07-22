#pragma once
#include "Application.h"
#include "Log.h" 

#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::CreateApplication();

int main()
{
	Hazel::Log::Init();
	auto app = Hazel::CreateApplication();
	app->Run();
	
	delete app;



	LOG("My Engine Log Msg");
	LOG_WARNING("My Engine Warnning Msg");
	LOG_ERROR("My Engine Error Msg");
}
#endif
