#pragma once
#include "Core.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"

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