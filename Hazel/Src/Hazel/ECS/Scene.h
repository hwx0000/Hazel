#pragma once
#include "Hazel.h"
#include "entt.hpp"
#include "GameObject.h"
#include "Components/Component.h"

namespace Hazel
{
	class Scene
	{
	public:
		GameObject& CreateGameObjectInScene();
		std::vector<GameObject>& GetGameObjects();// 一定返回的是&, 这里引起过Bug
		
		// 对Component的操作, 要通过Scene来完成, 是不是考虑让GameObject记录m_Registry的引用
		// 直接在GameObject上进行调用?
		template <class T>
		T& AddComponentForGameObject(GameObject& go, const T& component);

		template <class T>
		void RemoveComponentForGameObject(GameObject& go);
		
		template <class T>
		T& GetComponentInGameObject(const GameObject& go);

	private:
		entt::registry m_Registry;
		std::vector<GameObject> m_GameObjects;
	};
}