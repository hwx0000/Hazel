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

		GameObject& CreateGameObjectInScene(const std::shared_ptr<Scene>& ps, const std::string& name = "Default Name");
		std::vector<GameObject>& GetGameObjects();// 一定返回的是&, 这里引起过Bug
		GameObject& GetGameObjectById(uint32_t id, bool& success);
		
		template<class T>
		std::vector<std::shared_ptr<T>> GetComponents()
		{
			std::vector<std::shared_ptr<T>>res;
			auto& view = m_Registry.view<T>();
			for (auto& entity : view)
			{
				T& ref = view.get<T>(entity);
				res.push_back(std::shared_ptr<T>(&ref));
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

		// TODO: 后续可能要返回GameObject的指针
		template<class T>
		std::vector<GameObject> GetGameObjectsByComponent()
		{
			std::vector<GameObject> res;
			auto group = m_Registry.view<T>();
			for (auto entity : group)
			{
				std::vector<GameObject>::iterator itr =std::find(m_GameObjects.begin(), m_GameObjects.end(), entity);
				if (itr != m_GameObjects.end())
					res.push_back(*itr);
			}

			return res;
		}

		entt::registry& GetRegistry() { return m_Registry; }
		const entt::registry& GetRegistry() const { return m_Registry; }

		void DestroyGameObject(const GameObject& go);

		void DestroyGameObjectById(uint32_t id);

	private:
		entt::registry m_Registry;
		std::vector<GameObject> m_GameObjects;
	};
}