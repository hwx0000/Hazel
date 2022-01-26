#pragma once
#include "RendererAPI.h"

namespace Hazel
{
	class RenderCommand
	{
	public:
		static void DrawIndexed(const std::shared_ptr<VertexArray>&);
		static void Clear();
		static void ClearColor(const glm::vec4&);

	private:
		static Hazel::RendererAPI* s_RendererAPI;
	};
}