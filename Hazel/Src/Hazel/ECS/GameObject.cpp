#include "hzpch.h"
#include "GameObject.h"
#include "Components/Transform.h"
#include "Components/CameraComponent.h"

namespace Hazel
{
	GameObject::GameObject(const std::shared_ptr<Scene>& ps, const entt::entity & entity) : m_Scene(ps), m_InsanceId(entity)
	{
	}
}