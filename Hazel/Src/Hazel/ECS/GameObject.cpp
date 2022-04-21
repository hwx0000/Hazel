#include "hzpch.h"
#include "GameObject.h"
#include "Components/Transform.h"

namespace Hazel
{
	GameObject::GameObject(const std::shared_ptr<Scene>& ps, const entt::entity & entity) : m_Scene(ps), m_InsanceId(entity)
	{
	}

	template<class T, class ...Args>
	void GameObject::AddComponent(const T& component, Args&& ...args)
	{
		//auto s = new T(args...);
		std::shared_ptr<Scene> p = m_Scene.lock();
		
		if (p)
			p->GetRegistry().emplace<T>(m_InsanceId, std::forward<Args>(args)...);
	}

	template void GameObject::AddComponent<SpriteRenderer, glm::vec4>(const SpriteRenderer& component, glm::vec4&&);

	//go.AddComponent<Hazel::SpriteRenderer>(sr, glm::vec4{ 0.1f, 0.8f, 0.1f, 1.0f });

}