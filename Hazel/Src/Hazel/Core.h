#pragma once

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
	#define HAZEL_API _declspec (dllexport)
	#else 
	#define HAZEL_API _declspec (dllimport)
	#endif // HZ_BUILD_DLL
#endif