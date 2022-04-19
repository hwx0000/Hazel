#include "hzpch.h"
#include "Scene.h"

namespace Hazel
{
	GameObject& Scene::CreateGameObjectInScene()
	{
		m_GameObjects.push_back(m_Registry.create());
		return m_GameObjects[m_GameObjects.size() - 1];
	}

	std::vector<GameObject>& Scene::GetGameObjects()
	{
		return m_GameObjects;
	}

	template<class T>
	T& Scene::AddComponentForGameObject(GameObject & go, const T& component)
	{
		return NULL;//m_Registry.emplace<T>(go, T);
	}

	// TODO: 临时的写法, 只是为了让模板编译
	template<> 
	Hazel::SpriteRenderer& Scene::AddComponentForGameObject(GameObject & go, const Hazel::SpriteRenderer& component)
	{
		return m_Registry.emplace<Hazel::SpriteRenderer>(go, component);
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

	template<>
	SpriteRenderer& Scene::GetComponentInGameObject(const GameObject & go)
	{
		return m_Registry.get<SpriteRenderer>(go.m_InsanceId);
	}
}
