#pragma once
#include "Hazel/Renderer/Renderer.h"

class OpenGLRenderer : public Renderer
{
public:


	void BeginScene() override;

	void EndScene() override;

	void DrawIndexed(std::shared_ptr<VertexArray>& const) override;
};