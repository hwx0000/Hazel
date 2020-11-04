#pragma once
#include "Hazel/Core.h"
#include <utility>

namespace Hazel
{
	class HAZEL_API Input 
	{
	public:
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImp(button); }
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImp(keycode); }
		inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImp(); }

	protected:
		virtual bool IsKeyPressedImp(int keycode) = 0;
		virtual bool IsMouseButtonPressedImp(int button) = 0;
		virtual std::pair<float, float> GetMousePosImp() = 0;
	private:
		static Input* s_Instance;
	};
}