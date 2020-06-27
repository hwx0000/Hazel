#pragma once
#include "Application.h"

#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application *CreateApplication();

int main()
{
	auto app = CreateApplication();
	app->Run();
	delete app;
}
#endif
