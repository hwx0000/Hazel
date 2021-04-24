#include "hzpch.h"
#include "Renderer.h"

void Renderer::BeginScene()
{
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const std::shared_ptr<VertexArray>& va)
{
	va->Bind();
}
