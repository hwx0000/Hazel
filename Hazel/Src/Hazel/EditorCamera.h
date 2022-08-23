#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

namespace Hazel
{
	// 这应该是一个与渲染平台无关的类, 后续会派生为不同的平台对应的Camera?
	// 目前把它认为是一个2D的Camera, 因为目前相机的旋转只有一个维度
	class EditorCamera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };

	public:
		// 构造函数, 由于正交投影下, 需要Frustum, 默认near为-1, far为1, 就不写了
		// 不过这个构造函数没有指定Camera的位置, 所以应该是默认位置
		EditorCamera(ProjectionType type, float left, float right, float bottom, float top);
		void OnResize(uint32_t width, uint32_t height);

		// 读写Camera的位置和朝向, 这些数据是用于设置View矩阵的
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position);
		glm::quat GetRotation() const { return m_Rotation; }
		void SetRotation(glm::quat rotation);

		// 返回三个矩阵的接口, 这些数据用于设置Projection矩阵
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		void SetProjectionMatrix(float left, float right, float bottom, float top);
	
		bool IsProjectiveCamera() { return m_Type == ProjectionType::Perspective; }
		bool IsOrthographicCamera() { return m_Type == ProjectionType::Orthographic; }

		glm::vec3 GetLocalForward() { return m_Rotation * glm::vec3{ 0, 0, 1 }; }
		glm::vec3 GetLocalRight() { return m_Rotation * glm::vec3{ 1, 0, 0 }; }
		glm::vec3 GetLocalUp() { return m_Rotation * glm::vec3{ 0, 1, 0 }; }
		
	private:
		void RecalculateViewMatrix();
	
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;// 作为计算时的Cache

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;

		glm::vec3 m_Position = glm::vec3(0, 0, 3.0f);	// 正交投影下的相机位置不重要
		// WXYZ, 初始方向朝-Z方向
		glm::quat m_Rotation = { 0, 1, 0, 0 };// 正交投影下的相机只会有绕Z轴的旋转

		ProjectionType m_Type = ProjectionType::Perspective;
	};
}