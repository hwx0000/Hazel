#pragma once
#include "Application.h"
#include "Log.h" 

#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::CreateApplication();

int main()
{
	Hazel::Instrumentor::Get().BeginSession("Init SpdLog System", "InitSpdLog.json");
	Hazel::Log::Init();
	Hazel::Instrumentor::Get().EndSession();

	Hazel::Instrumentor::Get().BeginSession("Create Application", "CreateApplication.json");
	auto app = Hazel::CreateApplication();
	Hazel::Instrumentor::Get().EndSession();
	
	Hazel::Instrumentor::Get().BeginSession("Run Application", "RunApplication.json");
	app->Run();
	Hazel::Instrumentor::Get().EndSession();
	
	delete app;

	CORE_LOG("My Engine Log Msg");
	CORE_LOG_WARNING("My Engine Warnning Msg");
	CORE_LOG_ERROR("My Engine Error Msg");
}
#endif
