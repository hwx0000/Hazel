#include "hzpch.h"
#include "Scene.h"

namespace Hazel
{
	Scene::Scene()
	{
		m_ThisPtr = std::shared_ptr<Scene>(this);
	}

	Scene::~Scene()
	{
		m_Registry.clear();
		m_ThisPtr.reset();
	}

	GameObject& Scene::CreateGameObjectInScene()
	{
		GameObject go(m_ThisPtr, m_Registry.create());
		m_GameObjects.push_back(go);
		return m_GameObjects[m_GameObjects.size() - 1];
	}

	std::vector<GameObject>& Scene::GetGameObjects()
	{
		return m_GameObjects;
	}

	//template<class T>
	//T& Scene::AddComponentForGameObject(GameObject & go, const T& component)
	//{
	//	return NULL;//m_Registry.emplace<T>(go, T);
	//}

	//// TODO: 临时的写法, 只是为了让模板编译
	//template<> 
	//Hazel::SpriteRenderer& Scene::AddComponentForGameObject(GameObject & go, const Hazel::SpriteRenderer& component)
	//{
	//	return m_Registry.emplace<Hazel::SpriteRenderer>(go, component);
	//}

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

	template SpriteRenderer& Scene::GetComponentInGameObject(const GameObject & go);


	//template<>
	//SpriteRenderer& Scene::GetComponentInGameObject(const GameObject & go)
	//{
	//	return m_Registry.get<SpriteRenderer>(go.m_InsanceId);
	//}
}
