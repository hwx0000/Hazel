#pragma once
#include "Core/Core.h"
#include <utility>

namespace Hazel
{
	// 引擎提供给用户查询Input的类, 里面的静态public函数是给用户使用的
	// 里面的protected函数是给Input的子类使用的, 具体需要根据用户所在的平台决定使用哪种子类对象
	// 这里的keycode是用int表示的, 具体哪个Key, 代表值为多少的int, 被统一定义在了引擎的KeyCode.h文件里
	// 比如#define HZ_KEY_D                  68, 这种写法借鉴于glfw3.h
	class HAZEL_API Input 
	{
	public:
		static bool IsMouseButtonPressed(int button);
		static bool IsKeyPressed(int keycode);
		static std::pair<float, float> GetMousePos();
	};
}