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

	void Scene::Begin()
	{
	}

	void Scene::Pause()
	{
	}

	void Scene::Stop()
	{
	}

	void Scene::Clear()
	{
		ClearAllGameObjectsInScene();
	}

	void Scene::Update(const float& deltaTime)
	{

		// ----  Update Physics -----
		// TODO 物理部分的更新可能得稳定一分钟固定次数
		Physics2D::Update();

		// 根据Physics计算得到的rigidBody的结果, 反过来应用到GameObject的Transform上
		UpdateTransformsAfterPhysicsSim();
	}

	void Scene::OnViewportResized(uint32_t width, uint32_t height)
	{
		std::vector<CameraComponent*> cams = GetComponents<CameraComponent>();

		for (CameraComponent* cam : cams)
		{
			if (!cam->IsFixedAspectRatio())
				cam->SetAspectRatio(width, height);
		}
	}

	void Scene::ClearAllGameObjectsInScene()
	{
		m_GameObjects.clear();
	}

	GameObject& Scene::CreateGameObjectInScene(const std::shared_ptr<Scene>& ps, const std::string& name)
	{
		GameObject go(ps, m_Registry.create(), name);
		go.AddComponent<Transform>();
		m_GameObjects.push_back(go);
		return m_GameObjects[m_GameObjects.size() - 1];
	}

	GameObject& Scene::CreateGameObjectInSceneWithUUID(const std::shared_ptr<Scene>& ps, const uint64_t& id, const std::string& name)
	{
		GameObject go(ps, m_Registry.create(), id, name);
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

	void Scene::UpdateTransformsAfterPhysicsSim()
	{
		std::vector<GameObject>gos = GetGameObjectsByComponent<Rigidbody2D>();

		for (size_t i = 0; i < gos.size(); i++)
		{
			Rigidbody2D& rb = gos[i].GetComponent<Rigidbody2D>();
			Transform& t = gos[i].GetComponent<Transform>();

			t.Translation.x = rb.GetLocation().x;
			t.Translation.y = rb.GetLocation().y;
			t.Rotation.z = rb.GetAngle();
		}
	}
}
