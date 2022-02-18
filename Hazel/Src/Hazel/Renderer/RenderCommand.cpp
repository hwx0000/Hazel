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

	void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArr)
	{
		vertexArr->Bind();
		s_RendererAPI->DrawIndexed(vertexArr);
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
