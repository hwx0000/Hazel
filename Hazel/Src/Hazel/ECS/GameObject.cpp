#include "hzpch.h"
#include "GameObject.h"
#include "Components/Transform.h"
#include "Components/CameraComponent.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Hazel
{
	GameObject::GameObject(const std::shared_ptr<Scene>& ps, const entt::entity & entity, const std::string& name)
		: m_Scene(ps), m_InsanceId(entity), m_Name(name)
	{
	}

	glm::vec3 GameObject::GetPosition()
	{
		HAZEL_ASSERT(HasComponent<Transform>(), "GameObejct Missing TransformComponent");

		const glm::mat4 trans = GetComponent<Transform>();
		return glm::vec3(trans[3][0], trans[3][1], trans[3][2]);
	}

	glm::vec3 GameObject::GetPosition() const
	{
		HAZEL_ASSERT(HasComponent<Transform>(), "GameObejct Missing TransformComponent");

		const glm::mat4 trans = GetComponent<Transform>();
		return glm::vec3(trans[3][0], trans[3][1], trans[3][2]);
	}

	glm::mat4 GameObject::GetTransformMat()
	{
		HAZEL_ASSERT(HasComponent<Transform>(), "GameObejct Missing TransformComponent");
		return GetComponent<Transform>();
	}

	glm::mat4 GameObject::GetTransformMat() const
	{
		HAZEL_ASSERT(HasComponent<Transform>(), "GameObejct Missing TransformComponent");
		return GetComponent<Transform>();
	}
}