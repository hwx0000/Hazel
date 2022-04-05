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

		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// 添加各种类型的DrawQuad函数, 包含了position、rotation、texture、tiling和tintColor

		// Without Rotation
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = {1,1,1,1});
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = {1,1,1,1});

		// With Rotation
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotatedAngle, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotatedAngle, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotatedAngle, const std::shared_ptr<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = { 1,1,1,1 });
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotatedAngle, const std::shared_ptr<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = { 1,1,1,1 });

		// For Debuging
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