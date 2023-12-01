#pragma once
#include <memory>

namespace Hazel
{
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		uint32_t InstanceId = 0;
	};
}