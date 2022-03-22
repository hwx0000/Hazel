#pragma once
#include "hzpch.h"
#include "Hazel/Debug/Instrumentor.h"

namespace Hazel
{
	template<typename Fn>
	class Timer
	{
	public:
		// Timer的构造函数里接受一个Fn的右值, Fn代表一个callable object, 其参数为void(ProfileResult)
		// 在Timer的析构函数里会去调用它
		Timer(const char* name, Fn&& func)
			: m_Name(name), m_Func(func), m_Stopped(false)
		{
			// 构造函数里开始计时
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}

		~Timer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			// 结束计时
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			ProfileResult result;
			// 换算成秒
			result.Start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			result.End = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
			// get_id返回的是一个ID对象, 需要取Hash值作为thread id
			result.ThreadId = std::hash<std::thread::id>{}(std::this_thread::get_id());
			result.Name = m_Name;

			m_Stopped = true;
			// 调用m_Func
			m_Func(result);
		}

	private:
		const char* m_Name;
		Fn m_Func;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};
}
