#pragma once
#include "Component.h"
#include "box2d/box2d.h"

namespace Hazel
{
	enum class Rigidbody2DType
	{
		Static,
		Dynamic,
		Kinematic
	};

	class Rigidbody2D : public Component
	{
	public:
		Rigidbody2D(const std::shared_ptr<b2World>& world, const float& x = 0.0f, const float& y = 0.0f, Rigidbody2DType type = Rigidbody2DType::Static);

	private:
		b2BodyDef m_BodyDef;
		std::shared_ptr<b2Body> m_BodyPtr;
		Rigidbody2DType m_Type;
	};
}