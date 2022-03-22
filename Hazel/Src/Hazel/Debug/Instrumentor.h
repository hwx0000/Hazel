#pragma once
#include "hzpch.h"

namespace Hazel
{
	struct ProfileResult
	{
		const char* Name;
		size_t ThreadId;
		long long Start;
		long long End;
	};

	// Instrumentor是个单例, 但是应该不是线程安全的单例
	class Instrumentor
	{
	public:
		static Instrumentor& Get()
		{
			static Instrumentor instance;// 这一行只会执行一次
			return instance;
		}

		Instrumentor()
			: m_CurrentSessionName(""), m_ProfileCount(0)
		{
		}

		// 创建一个Stream, 写入对应的Header文件
		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			m_OutputStream.open(filepath);
			WriteHeader();
			m_CurrentSessionName = name;
		}

		// Stream里写入Footer文件, 结束Stream
		void EndSession()
		{
			WriteFooter();
			m_OutputStream.close();
			m_ProfileCount = 0;
		}

		// 需要在Timer的析构函数里, 也就是结束计时的时候, 调用函数, 把结果写入stream里
		void WriteProfile(const ProfileResult& result)
		{
			if (m_ProfileCount++ > 0)
				m_OutputStream << ",";

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			// 这样写也是为了符合Chrome Tracing的文件读取格式
			m_OutputStream << "{";
			m_OutputStream << "\"cat\":\"function\",";
			m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
			m_OutputStream << "\"name\":\"" << name << "\",";
			m_OutputStream << "\"ph\":\"X\",";
			m_OutputStream << "\"pid\":0,";
			m_OutputStream << "\"tid\":" << result.ThreadId << ",";
			m_OutputStream << "\"ts\":" << result.Start;
			m_OutputStream << "}";

			m_OutputStream.flush();
		}

		// 整个JSON文件的Header
		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
			m_OutputStream.flush();
		}

		// 整个JSON文件的Footer
		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

	private:
		std::string m_CurrentSessionName;
		std::ofstream m_OutputStream;
		int m_ProfileCount;
	};
}