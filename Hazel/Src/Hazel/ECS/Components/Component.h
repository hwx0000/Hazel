#pragma once
#include <memory>

namespace Hazel
{
	class Component
	{
	public:
		Component() = default;

		// Uncopieable but movable
		Component(const Component&) = delete;
		Component(Component&&) = default;

		Component& operator=(const Component&) = delete;
		Component& operator=(Component&&) = default;

		virtual ~Component() = default;

		uint32_t InstanceId = 0;

		//protected:
		//	std::weak_ptr<GameObject> m_GameObject;
	};
}