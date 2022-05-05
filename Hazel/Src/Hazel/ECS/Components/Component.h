#pragma once
#include <memory>

namespace Hazel
{
	class Component
	{
	public:
		virtual ~Component() = default;

	//protected:
	//	std::weak_ptr<GameObject> m_GameObject;
	};
}