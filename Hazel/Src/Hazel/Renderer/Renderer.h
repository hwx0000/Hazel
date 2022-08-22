#pragma once
#include "RendererAPI.h"
#include "VertexArray.h"
#include <memory>
#include "glm/glm.hpp"
#include "Hazel/EditorCamera.h"
#include "Shader.h"


namespace Hazel
{
	class Renderer
	{
	public:
		// 这个函数真的有必要放到Renderer类里吗, Renderer2D类也要放?
		static inline RendererAPI::APIType GetAPI() { return RendererAPI::GetAPIType(); }

		static void Init();
		static void BeginScene(const EditorCamera& camera);
		static void EndScene();
		// 绑定对应的VertexArray, 然后调用DrawCall
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
	private:
		// 对于不同的物体, MVP矩阵里的M都是不同的, 但是VP矩阵都是相同的
		// 所以这里归类在场景信息里
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};
}
