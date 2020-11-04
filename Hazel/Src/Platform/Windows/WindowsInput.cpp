#include "hzpch.h"
#include "WindowsInput.h"
#include <GLFW/glfw3.h>
#include "Hazel/Application.h"

namespace Hazel
{
	Input* Input::s_Instance = new WindowsInput();
	bool WindowsInput::IsKeyPressedImp(int keycode)
	{
		GLFWwindow* w = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto r = glfwGetKey(w, keycode);
		return r == GLFW_PRESS || r == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImp(int button)
	{
		GLFWwindow* w = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto r = glfwGetMouseButton(w, button);
		return r == GLFW_PRESS || r == GLFW_REPEAT;
		return false;
	}

	std::pair<float, float> WindowsInput::GetMousePosImp()
	{
		GLFWwindow* w = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(w, &x, &y);
		return std::pair<float, float>((float)x, (float)y);
	}

}