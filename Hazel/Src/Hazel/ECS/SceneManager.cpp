#include "hzpch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Components/Transform.h"
#include "Components/Rigidbody2D.h"
#include "Components/SpriteRenderer.h"

namespace Hazel
{
	SceneManager* SceneManager::s_InstancePtr = nullptr;

	std::shared_ptr<Scene> SceneManager::CopyScene(const Scene& src)
	{
		std::shared_ptr<Scene> scene = std::make_shared<Scene>();

		for (const GameObject& go : src.m_GameObjects)
		{
			entt::entity Entity = (entt::entity)go.GetInstanceId();
			GameObject& NewGo = scene->CreateGameObjectInScene(scene, go.GetName());
			NewGo.SetUUID(go.GetUUID());

			entt::registry& dstRegister = scene->GetRegistry();
			entt::entity dstEntity = (entt::entity)NewGo.GetInstanceId();

			// 遍历所有的Component, 寻找挂在Entity上的Component
			for (auto&& curr : src.m_Registry.storage())
			{
				auto& storage = curr.second;
				if (storage.contains(Entity))
				{
					entt::id_type id = curr.first;
					CopyComponentForGameObjectIfExists<Transform>(dstRegister, dstEntity, src.m_Registry, Entity, id);
					CopyComponentForGameObjectIfExists<SpriteRenderer>(dstRegister, dstEntity, src.m_Registry, Entity, id);
					CopyComponentForGameObjectIfExists<Rigidbody2D>(dstRegister, dstEntity, src.m_Registry, Entity, id);
					CopyComponentForGameObjectIfExists<CameraComponent>(dstRegister, dstEntity, src.m_Registry, Entity, id);
				}
			}
		}

		return scene;
	}
}