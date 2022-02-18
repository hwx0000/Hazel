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

		// 检查OpenGL版本
#ifdef HZ_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		HAZEL_CORE_ASSERT((versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5)), "Hazel requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLContext::SwapBuffer() 
	{
		glfwSwapBuffers(m_Window);
	}
}