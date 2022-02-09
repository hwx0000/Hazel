#include "hzpch.h"
#include "OpenGLContext.h"

namespace Hazel
{
	void OpenGLContext::Init() 
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		HAZEL_ASSERT(status, "Failed to init glad");

		CORE_LOG("OpenGL Info:");
		CORE_LOG("    Vendor: {0}", glGetString(GL_VENDOR));//打印厂商
		CORE_LOG("    Renderer: {0}", glGetString(GL_RENDERER));
		CORE_LOG("    Version: {0}", glGetString(GL_VERSION));

		glEnable(GL_BLEND);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	}

	void OpenGLContext::SwapBuffer() 
	{
		glfwSwapBuffers(m_Window);
	}
}