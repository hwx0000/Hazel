#pragma once
#include "RendererAPI.h"
#include "VertexArray.h"
#include <memory>
#include "glm/glm.hpp"
#include "Hazel/EditorCamera.h"
#include "Shader.h"
#include "Texture.h"
#include "SubTexture2D.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/CameraComponent.h"


namespace Hazel
{
	// 由于之前把RenderCommand拆分成了与平台无关的API, 这里的Renderer和Renderer2D都只需要调用
	// 抽象层的API即可
	class RenderCommandRegister
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const EditorCamera& camera);
		static void BeginScene(const CameraComponent& camera, const glm::mat4& transform);
		static void EndScene();

		// 添加各种类型的DrawQuad函数, 包含了position、rotation、texture、tiling和tintColor

		static void DrawSpriteRenderer(const SpriteRenderer& spriteRenderer, const glm::mat4& transform, uint32_t goId);

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = { 1,1,1,1 });
		static void DrawQuad(const glm::mat4& transform, const std::shared_ptr<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = { 1,1,1,1 });

		// For Debugging
		struct Statistics
		{
			uint32_t DrawCallCnt;
			uint32_t DrawQuadCnt;

			uint32_t DrawVerticesCnt() { return DrawQuadCnt * 4; }
			uint32_t DrawTrianglesCnt() { return DrawQuadCnt * 2; }
		};

		static Statistics GetStatistics();// 会在2DRendererData里存一个Statistics对象

	private:
		static void Flush();
		static void ResetBatchParams();
	};
}