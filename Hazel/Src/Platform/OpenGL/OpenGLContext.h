#pragma once
#include "Hazel/Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>
#include "glad/glad.h"

namespace Hazel
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* _handle) :
			m_Window(_handle) {}
		virtual void Init() override;
		virtual void SwapBuffer() override;
	private:
		GLFWwindow* m_Window;
	};
}