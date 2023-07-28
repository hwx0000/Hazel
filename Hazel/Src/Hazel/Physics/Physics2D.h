#pragma once
#include "box2d/box2d.h"
#include <memory>
#include "ECS/Components/Rigidbody2D.h"

namespace Hazel
{
	class Collider2D;
	class Rigidbody2D;

	// Pyhisics2DWorld
	class Physics2D
	{
		static const int velocityIterations = 6;
		static const int positionIterations = 1;

	public:
		static void Init(float gravityX = 0.0f, float gravityY = -10.0f);
		static void Update();
		static const std::shared_ptr<b2World>& GetWorld()  { return m_World; }

		static float GetFixedTimeStep() { return m_FixedTimeStep; }
		static float SetFixedTimeStep(const float& fixedTimeStep) { m_FixedTimeStep = fixedTimeStep; }

	private:
		static std::shared_ptr<b2World> m_World;
		static float m_FixedTimeStep;
	};
}