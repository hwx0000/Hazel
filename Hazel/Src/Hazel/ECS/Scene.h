#pragma once
#include "Hazel.h"
#include "entt.hpp"
#include "GameObject.h"
#include "Components/Component.h"

namespace Hazel
{
	class GameObject;
	class Scene
	{
	public:
		Scene();
		~Scene();

		void Update();

		GameObject& CreateGameObjectInScene(const std::shared_ptr<Scene>& ps);
		std::vector<GameObject>& GetGameObjects();// 一定返回的是&, 这里引起过Bug
		
		template<class T>
		void RemoveComponentForGameObject(GameObject& go)
		{
			m_Registry.remove<T>(go);
		}

		template<class T>
		T& GetComponentInGameObject(const GameObject& go)
		{
			return m_Registry.get<T>(go);
		}

		entt::registry& GetRegistry() { return m_Registry; }
		const entt::registry& GetRegistry() const { return m_Registry; }

	private:
		entt::registry m_Registry;
		std::vector<GameObject> m_GameObjects;
	};
}