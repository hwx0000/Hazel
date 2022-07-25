#include "hzpch.h"
#include "GameObject.h"
#include "Components/Transform.h"
#include "Components/CameraComponent.h"

namespace Hazel
{
	GameObject::GameObject(const std::shared_ptr<Scene>& ps, const entt::entity & entity, const std::string& name)
		: m_Scene(ps), m_InsanceId(entity), m_Name(name)
	{
	}
}