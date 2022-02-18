#include "hzpch.h"
#include "OpenGLRendererAPI.h"
#include "glad/glad.h"

namespace Hazel
{
	void OpenGLRendererAPI::Init() const
	{
		glEnable(GL_BLEND);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	}

	void OpenGLRendererAPI::Clear() const
	{
		// TODO: 后期会添加flag
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) const
	{
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArr) const
	{
		glDrawElements(GL_TRIANGLES, vertexArr->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
