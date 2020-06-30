#pragma once
#include "Application.h"
#include "Log.h" 

#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application *CreateApplication();

int main()
{
	auto app = CreateApplication();
	app->Run();
	delete app;

	Hazel::Log::Init();
	LOG("My Engine Log Msg");
	LOG_WARNING("My Engine Warnning Msg");
	LOG_ERROR("My Engine Error Msg");
}
#endif
