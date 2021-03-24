#include "hzpch.h"
#include "OpenGLContext.h"

namespace Hazel
{
	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HAZEL_ASSERT(status, "Failed to init glad");
	}

	void OpenGLContext::SwapBuffer() {
		glfwSwapBuffers(m_Window);
	}
}