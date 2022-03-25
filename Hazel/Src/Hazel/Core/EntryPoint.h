#pragma once
#include "Application.h"
#include "Log.h" 

#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::CreateApplication();

int main()
{
	HAZEL_PROFILE_BEGIN_SESSION("Init SpdLog System", "InitSpdLog.json");
	Hazel::Log::Init();
	HAZEL_PROFILE_END_SESSION();

	HAZEL_PROFILE_BEGIN_SESSION("Create Application", "CreateApplication.json");
	auto app = Hazel::CreateApplication();
	HAZEL_PROFILE_END_SESSION();
	
	HAZEL_PROFILE_BEGIN_SESSION("Run Application", "RunApplication.json");
	app->Run();
	HAZEL_PROFILE_END_SESSION();
	
	delete app;

	CORE_LOG("My Engine Log Msg");
	CORE_LOG_WARNING("My Engine Warnning Msg");
	CORE_LOG_ERROR("My Engine Error Msg");
}
#endif
