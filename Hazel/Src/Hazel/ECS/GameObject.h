#pragma once
#include "entt.hpp"
#include "Scene.h"

namespace Hazel
{
	class Scene;
	class GameObject
	{
	public:
		GameObject(const std::shared_ptr<Scene>& ps, const entt::entity& entity, const std::string& name = "Default GameObject");

		template<class T, class... Args>
		// todo, 应该返回创建的Component, 模板函数都应该放到.h文件里
		T& AddComponent(Args&& ...args)
		{
			//auto s = new T(args...);
			std::shared_ptr<Scene> p = m_Scene.lock();

			if (p)
				return p->GetRegistry().emplace<T>(m_InsanceId, std::forward<Args>(args)...);
		}

		template<class T>
		bool HasComponent()
		{
			std::shared_ptr<Scene> p = m_Scene.lock();

			if (p)
				return p->GetRegistry().all_of<T>();

			return false;
		}

		template<class T>
		T& GetComponent()
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


	private:
		entt::entity m_InsanceId;
		std::weak_ptr<Scene> m_Scene;
		std::string m_Name;
	};
}