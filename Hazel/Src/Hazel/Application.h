#pragma once
#include "Core.h"

namespace Hazel
{
	//_declspec(dllexport) class Application
	class HAZEL_API Application
	{
	public:
		Application() {};
		virtual ~Application()
		{

		}

		void Run();
	};
}