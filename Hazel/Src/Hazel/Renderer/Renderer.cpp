#include "hzpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace Hazel
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();// 最后的()居然可以去掉

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(const EditorCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& va, 
		const glm::mat4& transform)
	{
		shader->Bind();           
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		RenderCommand::DrawIndexed(va);
	}
}
