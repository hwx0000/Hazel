#pragma once
#include "Component.h"
#include "glm/glm.hpp"

namespace Hazel
{
	class CameraComponent : public Component
	{
	public:
		CameraComponent(float left, float right, float bottom, float top);

		glm::mat4 GetProjectionMatrix() { return m_Projection; }
		glm::mat4 GetProjectionMatrix() const { return m_Projection; }

		void SetRenderTargetSize(uint32_t width, uint32_t height) { m_RenderTargetWidth = width, m_RenderTargetHeight = height; }
		uint32_t GetRenderTargetWidth() { return m_RenderTargetWidth; }
		uint32_t GetRenderTargetHeight() { return m_RenderTargetHeight; }

	private:
		glm::mat4 m_Projection;// Camera的View矩阵由对应的Transform来记录
		uint32_t m_RenderTargetWidth, m_RenderTargetHeight;
	};
}