#pragma once
#include "RendererAPI.h"
#include "VertexArray.h"
#include <memory>
#include "glm/glm.hpp"
#include "Hazel/OrthographicCamera.h"
#include "Shader.h"
#include "Texture.h"


namespace Hazel
{
	// 由于之前把RenderCommand拆分成了与平台无关的API, 这里的Renderer和Renderer2D都只需要调用
	// 抽象层的API即可
	class Renderer2D
	{
	public:
		static inline RendererAPI::APIType GetAPI() { return RendererAPI::GetAPIType(); }

		static void Init();
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, std::shared_ptr<Texture>);

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