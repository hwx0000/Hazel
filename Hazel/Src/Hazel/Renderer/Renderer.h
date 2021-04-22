#pragma once
#include "RendererAPI.h"
#include "VertexArray.h"
#include <memory>
#include "glm/glm.hpp"


class Renderer
{
public:
	static inline RendererAPI::APIType GetAPI() { return RendererAPI::GetAPIType(); }

	virtual void BeginScene() = 0;
	virtual void EndScene() = 0;
	virtual void DrawIndexed(std::shared_ptr<VertexArray>& const) = 0;
};
