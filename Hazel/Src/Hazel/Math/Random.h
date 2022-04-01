#pragma once
#include <random>

// 这个macro是因为windows.h里的max宏跟std::numeric_limit里的max重定义了
#ifdef max
#undef max
#endif

namespace Hazel
{
	class Random
	{
	public:
		static void Init()
		{
			s_RandomEngine.seed(std::random_device()());
		}

		// 返回[0, 1]范围内的随机浮点数
		static float Float()
		{
			return (float)s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max();
		}
	private:
		static std::mt19937 s_RandomEngine;
		static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
	};
}