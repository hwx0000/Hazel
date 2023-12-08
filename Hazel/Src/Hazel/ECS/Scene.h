#pragma once
#include "Hazel.h"
#include "entt.hpp"
#include "GameObject.h"
#include "Components/Component.h"

namespace Hazel
{
	class GameObject;
	class SceneManager;
	class Scene
	{
		friend SceneManager;

	public:
		Scene();
		~Scene();

		void Begin();
		void Pause();
		void Stop();
		void Update(const float& deltaTime);

		void OnViewportResized(uint32_t width, uint32_t height);

		// TODO: 删除所有的GameObjects in scene
		void ClearAllGameObjectsInScene();

		GameObject& CreateGameObjectInScene(const std::shared_ptr<Scene>& ps, const std::string& name = "Default Name");
		GameObject& CreateGameObjectInSceneWithUUID(const std::shared_ptr<Scene>& ps, const uint64_t& id, const std::string& name = "Default Name");
		std::vector<GameObject>& GetGameObjects();// 一定返回的是&, 这里引起过Bug
		bool GetGameObjectById(uint64_t id, GameObject& inOutGo);
		
		CameraComponent* GetMainCamera();

		// TODO: 没有想到更好的办法能不用raw pointers, 如果返回shared_ptr, 则外部会在调用后, 
		// 会因为引用计数变为0而销毁T对象
		// This function will return all GetAllComponents in scene, if T is derived type
		// base class component will not be returned
		template<class T>
		std::vector<T*> GetAllComponents()
		{
			std::vector<T*> res;
			auto& view = m_Registry.view<T>();
			for (auto& entity : view)
			{
				T& ref = view.get<T>(entity);
				res.push_back(&ref);
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

		template<class T>
		void CopyComponent(const entt::registry& src, entt::registry& dst)
		{
			T component = src.get<T>();
			dst.emplace_or_replace(component, component.InstanceId);
		}

		entt::registry& GetRegistry() { return m_Registry; }
		const entt::registry& GetRegistry() const { return m_Registry; }

		void DestroyGameObject(const GameObject& go);

		void DestroyGameObjectById(uint64_t id);

	private:
		void UpdateTransformsAfterPhysicsSim();

	private:
		entt::registry m_Registry;
		std::vector<GameObject> m_GameObjects;
	};
}