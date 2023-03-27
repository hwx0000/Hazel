#include "hzpch.h"
#include "Physics2D.h"

namespace Hazel
{
	void Physics2D::Init(float gravityX, float gravityY)
	{
		// b2World is the physics hub that manages memory, objects, and simulation.
		b2Vec2 gravity(gravityX, -gravityY);
		b2World world(gravity);// 创建世界时需要设置重力加速度
	}

	void Physics2D::Update()
	{
		m_World->Step(m_FixedTimeStep, velocityIterations, positionIterations);
	}
	
	std::shared_ptr<Collider2D> Physics2D::CreateCollider2D()
	{
		return std::shared_ptr<Collider2D>();
	}

	std::shared_ptr<Rigidbody2D> Physics2D::CreateRigidbody2D()
	{
		return std::shared_ptr<Rigidbody2D>();
	}
}