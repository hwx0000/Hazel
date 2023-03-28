#pragma once
#include "Component.h"
#include "box2d/box2d.h"

namespace Hazel
{
	class Collider2D : public Component
	{
		enum class Shape2D
		{
			Box,
			Circle
		};

	public:


	private:
		b2PolygonShape m_Shape;
	};
}