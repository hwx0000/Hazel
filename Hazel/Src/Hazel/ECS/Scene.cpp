#include "hzpch.h"
#include "Scene.h"
#include "ECS/Components/Transform.h"

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

	void Scene::OnViewportResized(uint32_t width, uint32_t height)
	{
		std::vector<std::shared_ptr<CameraComponent>> cams = GetComponents<CameraComponent>();

		for (std::shared_ptr<CameraComponent>& cam : cams)
		{
			if (!cam->IsFixedAspectRatio())
			{
				cam -> SetAspectRatio(width, height);
			}
		}
	}

	GameObject& Scene::CreateGameObjectInScene(const std::shared_ptr<Scene>& ps, const std::string& name)
	{
		GameObject go(ps, m_Registry.create(), name);
		go.AddComponent<Transform>();
		m_GameObjects.push_back(go);
		return m_GameObjects[m_GameObjects.size() - 1];
	}

	std::vector<GameObject>& Scene::GetGameObjects()
	{
		return m_GameObjects;
	}

	GameObject& Scene::GetGameObjectById(uint32_t id, bool& success)
	{
		for (size_t i = 0; i < m_GameObjects.size(); i++)
		{
			if (m_GameObjects[i].GetInstanceId() == id)
			{
				success = true;
				return m_GameObjects[i];
			}
		}

		success = false;
		GameObject empty;
		return empty;
	}

	void Scene::DestroyGameObject(const GameObject& go)
	{
		for (std::vector<GameObject>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
		{
			if (*it == go)
			{
				m_GameObjects.erase(it);
				return;
			}
		}
	}

	void Scene::DestroyGameObjectById(uint32_t id)
	{
		bool suc = false;
		auto& go = GetGameObjectById(id, suc);
		if(suc)
			DestroyGameObject(go);
	}
}
