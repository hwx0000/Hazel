#pragma once
#include "entt.hpp"
#include "Scene.h"

namespace Hazel
{
	class Scene;
	class GameObject
	{
	public:
		GameObject(const std::shared_ptr<Scene>& ps, const entt::entity& entity);

		template<class T, class... Args>
		void AddComponent(const T& component, Args&&... arguments);

		operator entt::entity()  { return m_InsanceId; }
		operator entt::entity() const { return m_InsanceId; }

	private:
		entt::entity m_InsanceId;
		std::weak_ptr<Scene> m_Scene;
	};
}