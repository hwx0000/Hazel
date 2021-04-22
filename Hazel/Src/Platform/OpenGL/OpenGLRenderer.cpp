#include "hzpch.h"
#include "OpenGLRenderer.h"
#include "glad/glad.h"

void OpenGLRenderer::BeginScene()
{
}

void OpenGLRenderer::EndScene()
{
}

void OpenGLRenderer::DrawIndexed(std::shared_ptr<VertexArray>& const vertexArray)
{
	vertexArray->Bind();
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
