#pragma once
#include "entt.hpp"

namespace Hazel
{
	class GameObject
	{
	public:
		GameObject(const entt::entity& entity) :m_InsanceId(entity) {}

		operator entt::entity()  { return m_InsanceId; }
		operator entt::entity() const { return m_InsanceId; }

	//private:
		entt::entity m_InsanceId;
	};
}