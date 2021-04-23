#pragma once
#include "Hazel/Renderer/RendererAPI.h"

class OpenGLRendererAPI : public RendererAPI
{
public:

	// Inherited via RendererAPI
	virtual void Clear() const override;

	virtual void SetClearColor(const glm::vec4 &) const override;

	virtual void DrawIndexed(const std::shared_ptr<VertexArray>&) const override;
};