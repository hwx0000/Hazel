#pragma once
#include "box2d/box2d.h"
#include <memory>
//#include "Hazel/ECS/Components/"

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
		void Init(float gravityX = 0.0f, float gravityY = -10.0f);
		void Update();
		std::shared_ptr<Collider2D> CreateCollider2D();
		std::shared_ptr<Rigidbody2D> CreateRigidbody2D();

		float GetFixedTimeStep() const { return m_FixedTimeStep; }
		float SetFixedTimeStep(const float& fixedTimeStep) { m_FixedTimeStep = fixedTimeStep; }

	private:
		std::shared_ptr<b2World> m_World;
		float m_FixedTimeStep;
	};
}