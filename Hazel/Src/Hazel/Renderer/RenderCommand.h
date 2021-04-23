#pragma once
#include "RendererAPI.h"

class RenderCommand 
{
public:
	static void DrawIndexed(std::shared_ptr<VertexArray>&);
	static void Clear();
	static void ClearColor(const glm::vec4&);

private:
	static RendererAPI* s_RendererAPI;
};