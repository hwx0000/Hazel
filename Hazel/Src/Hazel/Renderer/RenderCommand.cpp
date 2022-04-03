#include "hzpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

	void RenderCommand::Init()
	{
		s_RendererAPI->Init();
	}

	// 调用此API之前, 绑定了什么Shader, 就用对应的Shader绘制这个vertex array
	void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArr, uint32_t count)
	{
		vertexArr->Bind();
		s_RendererAPI->DrawIndexed(vertexArr, count);
	}

	void RenderCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RenderCommand::ClearColor(const glm::vec4 &color)
	{
		s_RendererAPI->SetClearColor(color);
	}
}
