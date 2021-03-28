#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Hazel
{
	class HAZEL_API Log
	{
	public:
		Log();
		~Log();
		static void Init();
		static inline std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static inline std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger>s_CoreLogger;
		static std::shared_ptr<spdlog::logger>s_ClientLogger;
	};
}

// �������Client��Log
#define LOG(...)				::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARNING(...)		::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)			::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)

// �������ʵ���������̵�CommandLine��Log
#define CORE_LOG(...)			::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_LOG_WARNING(...)   ::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_LOG_ERROR(...)     ::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)