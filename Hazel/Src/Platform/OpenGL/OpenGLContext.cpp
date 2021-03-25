#include "hzpch.h"
#include "OpenGLContext.h"

namespace Hazel
{
	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HAZEL_ASSERT(status, "Failed to init glad");

		LOG("OpenGL Info:");
		LOG("    Vendor: {0}", glGetString(GL_VENDOR));//��ӡ����
		LOG("    Renderer: {0}", glGetString(GL_RENDERER));
		LOG("    Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffer() {
		glfwSwapBuffers(m_Window);
	}
}