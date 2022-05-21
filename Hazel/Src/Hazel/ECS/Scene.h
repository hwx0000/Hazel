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
		void OnViewportResized(uint32_t width, uint32_t height);

		GameObject& CreateGameObjectInScene(const std::shared_ptr<Scene>& ps);
		std::vector<GameObject>& GetGameObjects();// 一定返回的是&, 这里引起过Bug
		
		template<class T>
		std::vector<std::shared_ptr<T>> GetComponents()
		{
			std::vector<std::shared_ptr<T>>res;
			auto view = m_Registry.view<T>();
			for (auto entity : view)
			{
				T& ref = view.get<T>(entity);
				res.push_back(std::make_shared<T>(ref));
			}

			return res;
		}

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