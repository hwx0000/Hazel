#pragma once
#include "Hazel/Renderer/RendererAPI.h"

namespace Hazel
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() const override;

		// Inherited via RendererAPI
		virtual void Clear() const override;

		virtual void SetClearColor(const glm::vec4 &) const override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>&, uint32_t count) const override;

		void UpdateDowngradingMSAATexture();
	};
}