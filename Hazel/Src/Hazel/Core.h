#pragma once

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
	#define HAZEL_API _declspec (dllexport)
	#define IMGUI_API _declspec (dllexport)
	#else 
	#define HAZEL_API _declspec (dllimport)
	#define IMGUI_API _declspec (dllimport)
	#endif // HZ_BUILD_DLL
#endif


#ifdef HZ_ENABLE_ASSERTS
	#define HAZEL_ASSERT(x, ...) if(!x) {LOG_ERROR("Assertion Failed At: {0}", __VA_ARGS__);\
	__debugbreak();}
	#define HAZEL_CORE_ASSERT(x, ...) if(!x) {CORE_LOG_ERROR("Assertion Failed At: {0}", __VA_ARGS__);\
	__debugbreak();}
#else
	#define HAZEL_ASSERT(x, ...)
	#define HAZEL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) 1 << x 
