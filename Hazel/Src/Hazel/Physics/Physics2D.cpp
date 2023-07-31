#include "hzpch.h"
#include "Physics2D.h"

namespace Hazel
{
	std::shared_ptr<b2World> Physics2D::m_World = nullptr;
	float Physics2D::m_FixedTimeStep = 0.0f;

	void Physics2D::Init(float gravityX, float gravityY)
	{
		if (m_World == nullptr)
		{
			// 创建世界时需要设置重力加速度
			b2Vec2 gravity(gravityX, gravityY);
			// b2World is the physics hub that manages memory, objects, and simulation.
			m_World = std::make_shared<b2World>(gravity);
		}

		m_FixedTimeStep = 1.f / 60.f;
	}

	void Physics2D::Update()
	{
		m_World->Step(m_FixedTimeStep, velocityIterations, positionIterations);
	}
}