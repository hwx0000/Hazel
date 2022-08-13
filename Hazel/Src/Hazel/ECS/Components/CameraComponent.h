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
		CameraComponent();

		glm::mat4 GetProjectionMatrix() { return m_Projection; }
		glm::mat4 GetProjectionMatrix() const { return m_Projection; }

		void SetAspectRatio(uint32_t width, uint32_t height);

		void SetRenderTargetSize(uint32_t width, uint32_t height) { m_RenderTargetWidth = width, m_RenderTargetHeight = height; }
		uint32_t GetRenderTargetWidth() { return m_RenderTargetWidth; }
		uint32_t GetRenderTargetHeight() { return m_RenderTargetHeight; }


		bool& GetFixedAspectRatio() { return m_FixedAspectRatio; }
		bool IsFixedAspectRatio() const { return m_FixedAspectRatio; }

		ProjectionType GetProjectionType() { return m_ProjectionType; }
		void SetProjectionType(const ProjectionType& type) { m_ProjectionType = type; }

		float GetPerspectiveVerticalFOV() const { return m_PerspectiveFOV; }
		void SetPerspectiveVerticalFOV(float verticalFov) { m_PerspectiveFOV = verticalFov; RecalculateProjectionMat(); }
		float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
		void SetPerspectiveNearClip(float nearClip) { m_PerspectiveNear = nearClip; RecalculateProjectionMat(); }
		float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
		void SetPerspectiveFarClip(float farClip) { m_PerspectiveFar = farClip; RecalculateProjectionMat(); }

		float GetOrthographicSize() const { return m_OrthographicSize; }
		void SetOrthographicSize(float size) { m_OrthographicSize = size; RecalculateProjectionMat(); }
		float GetOrthographicNearClip() const { return m_OrthographicNear; }
		void SetOrthographicNearClip(float nearClip) { m_OrthographicNear = nearClip; RecalculateProjectionMat(); }
		float GetOrthographicFarClip() const { return m_OrthographicFar; }
		void SetOrthographicFarClip(float farClip) { m_OrthographicFar = farClip; RecalculateProjectionMat(); }

		void RecalculateProjectionMat();

	private:
		ProjectionType m_ProjectionType = ProjectionType::Orthographic;

		glm::mat4 m_Projection;// Camera的View矩阵由对应的Transform来记录
		uint32_t m_RenderTargetWidth, m_RenderTargetHeight;
		bool m_FixedAspectRatio = false;
		float m_AspectRatio = 1.77778f;

		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

		float m_PerspectiveFOV = glm::radians(45.0f);
		float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1000.0f;
	};
}