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
		m_GameObjects.push_back(go);
		return m_GameObjects[m_GameObjects.size() - 1];
	}

	std::vector<GameObject>& Scene::GetGameObjects()
	{
		return m_GameObjects;
	}
}
