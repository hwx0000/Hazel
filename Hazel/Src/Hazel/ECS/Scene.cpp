#include "hzpch.h"
#include "Scene.h"

namespace Hazel
{
	GameObject& Scene::CreateGameObjectInScene()
	{
		return GameObject(m_Registry.create());
	}

	template<class T>
	T& Scene::AddComponentForGameObject(GameObject & go, std::shared_ptr<T> component)
	{
		return m_Registry.emplace<T>(go, *component);
	}

	template<class T>
	void Scene::RemoveComponentForGameObject(GameObject& go)
	{
		m_Registry.remove<T>(go);
	}

	template<class T>
	T& Scene::GetComponentInGameObject(const GameObject & go)
	{
		return m_Registry.get<T>(go);
	}
}
