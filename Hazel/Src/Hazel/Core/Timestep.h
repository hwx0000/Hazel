#pragma once

namespace Hazel
{
	// Timestep 实际就是一个float值的wrapper
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{
		}

		operator float() const { return m_Time; }
		// 给float添加wrapper是方便进行秒和毫秒的转换
		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};
}