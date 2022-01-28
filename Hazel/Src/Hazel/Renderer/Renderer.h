#pragma once
#include "RendererAPI.h"
#include "VertexArray.h"
#include <memory>
#include "glm/glm.hpp"
#include "OrthographicCamera.h"
#include "Shader.h"


namespace Hazel
{
	class Renderer
	{
	public:
		static inline RendererAPI::APIType GetAPI() { return RendererAPI::GetAPIType(); }

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		// 绑定对应的VertexArray, 然后调用DrawCall
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
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
