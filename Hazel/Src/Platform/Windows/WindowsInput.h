#pragma once
#include "Hazel/Input.h"

namespace Hazel
{
	class WindowsInput : public Input
	{
	public:
		virtual bool IsKeyPressedImp(int keycode);
		virtual bool IsMouseButtonPressedImp(int button);
		virtual std::pair<float, float> GetMousePosImp();
	};
}