#include "hzpch.h"
#include <GLFW/glfw3.h>
#include "Core/Application.h"
#include "Core/Input.h"

namespace Hazel
{
	bool Input::IsKeyPressed(int keycode)
	{
		GLFWwindow* w = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto r = glfwGetKey(w, keycode);
		
		return r == GLFW_PRESS || r == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		GLFWwindow* w = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto r = glfwGetMouseButton(w, button);
		return r == GLFW_PRESS || r == GLFW_REPEAT;
		return false;
	}

	std::pair<float, float> Input::GetMousePos()
	{
		GLFWwindow* w = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(w, &x, &y);
		return std::pair<float, float>((float)x, (float)y);
	}

}