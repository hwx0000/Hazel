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
		HAZEL_ASSERT(HasComponent<Transform>(), "GameObject Missing TransformComponent");
		return GetComponent<Transform>().Translation;
	}

	glm::vec3 GameObject::GetPosition() const
	{
		HAZEL_ASSERT(HasComponent<Transform>(), "GameObject Missing TransformComponent");
		return GetComponent<Transform>().Translation;
	}

	void GameObject::SetPosition(const glm::vec3& p) 
	{
		HAZEL_ASSERT(HasComponent<Transform>(), "GameObject Missing TransformComponent");
		GetComponent<Transform>().Translation = p;
	}

	glm::mat4 GameObject::GetTransformMat()
	{
		HAZEL_ASSERT(HasComponent<Transform>(), "GameObject Missing TransformComponent");
		return GetComponent<Transform>().GetTransformMat();
	}

	glm::mat4 GameObject::GetTransformMat() const
	{
		HAZEL_ASSERT(HasComponent<Transform>(), "GameObject Missing TransformComponent");
		return GetComponent<Transform>().GetTransformMat();
	}

	void GameObject::SetTransformMat(const glm::mat4& trans)
	{
		HAZEL_ASSERT(HasComponent<Transform>(), "GameObject Missing TransformComponent");
		return GetComponent<Transform>().SetTransformMat(trans);
	}
}