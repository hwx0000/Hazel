#include "hzpch.h"
#include "Rigidbody2D.h"

namespace Hazel
{
	Rigidbody2D::Rigidbody2D(const std::shared_ptr<b2World>& world, const float& x, const float& y, Rigidbody2DType type) : m_Type(type)
	{
		//m_BodyDef.position.Set(0.0f, -10.0f);
		//m_BodyPtr.reset(*world->CreateBody(&m_BodyDef));
		//m_BodyPtr = std::make_shared<b2Body>(*);
	}
}