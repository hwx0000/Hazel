#pragma once
#include "RendererAPI.h"
#include "VertexArray.h"
#include <memory>
#include "glm/glm.hpp"


class Renderer
{
public:
	static inline RendererAPI::APIType GetAPI() { return RendererAPI::GetAPIType(); }

	static void BeginScene();
	static void EndScene();
	static void Submit(const std::shared_ptr<VertexArray>&);
};
