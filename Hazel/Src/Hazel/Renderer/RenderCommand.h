#pragma once
#include "RendererAPI.h"

namespace Hazel
{
	class RenderCommand
	{
	public:
		static void Init();
		static void DrawIndexed(const std::shared_ptr<VertexArray>&, uint32_t count = 0);
		static void Clear();
		static void ClearColor(const glm::vec4&);

	private:
		static Hazel::RendererAPI* s_RendererAPI;
	};
}