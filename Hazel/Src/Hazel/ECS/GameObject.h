#pragma once
#include "entt.hpp"
#include "Scene.h"
#include "UUID.h"

namespace Hazel
{
	class Scene;
	class GameObject
	{
	public:
		GameObject() = default;
		GameObject(const std::shared_ptr<Scene>& ps, const entt::entity& entity, const std::string& name = "Default GameObject");
		GameObject(const std::shared_ptr<Scene>& ps, const entt::entity& entity, const uint64_t& id, const std::string& name = "Default GameObject");

		template<class T, class... Args>
		T& AddComponent(Args&& ...args)
		{
			std::shared_ptr<Scene> p = m_Scene.lock();

			// Hazel这里存了Scene的Raw Pointer
			auto& com = p->GetRegistry().emplace<T>(m_InsanceId, std::forward<Args>(args)...);
			com.InstanceId = (uint32_t)m_InsanceId;
			return com;
		}

		template<class T>
		bool HasComponent()
		{
			std::shared_ptr<Scene> p = m_Scene.lock();

			if (p)
				return p->GetRegistry().all_of<T>(m_InsanceId);

			return false;
		}

		template<class T>
		bool HasComponent() const
		{
			std::shared_ptr<Scene> p = m_Scene.lock();

			if (p)
				return p->GetRegistry().all_of<T>(m_InsanceId);

			return false;
		}

		template<class T>
		T& GetComponent()
		{
			HAZEL_ASSERT(HasComponent<T>(), "GameObject Does Not Have The Specified Component!")

				std::shared_ptr<Scene> p = m_Scene.lock();

			return p->GetRegistry().get<T>(m_InsanceId);
		}

		template<class T>
		T& GetComponent() const
		{
			HAZEL_ASSERT(HasComponent<T>(), "GameObject Does Not Have The Specified Component!")

				std::shared_ptr<Scene> p = m_Scene.lock();

			return p->GetRegistry().get<T>(m_InsanceId);
		}


		operator entt::entity() { return m_InsanceId; }
		operator entt::entity() const { return m_InsanceId; }

		void SetName(const std::string& name) { m_Name = name; }
		const std::string& ToString() CONST { return m_Name; }
		//std::string& ToString() { return m_Name; }
		const uint32_t GetInstanceId() const { return (uint32_t)m_InsanceId; }
		const uint64_t GetUUID() const { return (*m_ID); }


		glm::vec3 GetPosition();
		glm::vec3 GetPosition() const;

		void SetPosition(const glm::vec3& p);

		glm::mat4 GetTransformMat();
		glm::mat4 GetTransformMat() const;

		void SetTransformMat(const glm::mat4& trans);
	private:
		entt::entity m_InsanceId;
		std::weak_ptr<Scene> m_Scene;
		std::string m_Name;
		std::shared_ptr<UUID> m_ID;
	};
}