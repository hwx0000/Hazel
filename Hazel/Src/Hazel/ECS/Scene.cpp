#include "hzpch.h"
#include "Scene.h"

namespace Hazel
{
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
		m_Registry.clear();
	}

	void Scene::Update()
	{
	}

	GameObject& Scene::CreateGameObjectInScene(const std::shared_ptr<Scene>& ps)
	{
		GameObject go(ps, m_Registry.create());
		m_GameObjects.push_back(go);
		return m_GameObjects[m_GameObjects.size() - 1];
	}

	std::vector<GameObject>& Scene::GetGameObjects()
	{
		return m_GameObjects;
	}
}
