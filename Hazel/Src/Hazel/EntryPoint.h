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



	CORE_LOG("My Engine Log Msg");
	CORE_LOG_WARNING("My Engine Warnning Msg");
	CORE_LOG_ERROR("My Engine Error Msg");
}
#endif
