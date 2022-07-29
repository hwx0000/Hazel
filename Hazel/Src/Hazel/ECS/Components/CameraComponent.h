#pragma once
#include "Component.h"
#include "glm/glm.hpp"

namespace Hazel
{
	// 暂时默认CameraComponent里的Camera都是Orthographic类型
	class CameraComponent : public Component
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };

	public:
		CameraComponent(float left, float right, float bottom, float top);

		glm::mat4 GetProjectionMatrix() { return m_Projection; }
		glm::mat4 GetProjectionMatrix() const { return m_Projection; }

		void SetAspectRatio(uint32_t width, uint32_t height);

		void SetRenderTargetSize(uint32_t width, uint32_t height) { m_RenderTargetWidth = width, m_RenderTargetHeight = height; }
		uint32_t GetRenderTargetWidth() { return m_RenderTargetWidth; }
		uint32_t GetRenderTargetHeight() { return m_RenderTargetHeight; }

		bool IsFixedAspectRatio() const { return m_FixedAspectRatio; }

		ProjectionType GetProjectionType() { return m_ProjectionType; }
		void SetProjectionType(const ProjectionType& type) { m_ProjectionType = type; }

	private:
		ProjectionType m_ProjectionType = ProjectionType::Orthographic;

		glm::mat4 m_Projection;// Camera的View矩阵由对应的Transform来记录
		uint32_t m_RenderTargetWidth, m_RenderTargetHeight;
		bool m_FixedAspectRatio = false;
		float m_AspectRatio;

		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;
	};
}