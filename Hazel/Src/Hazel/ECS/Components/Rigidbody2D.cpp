#include "hzpch.h"
#include "Rigidbody2D.h"
#include "Physics/Physics2D.h"

namespace Hazel
{
	b2BodyType Rigidbody2DTypeToB2BodyType(const Rigidbody2DType& type)
	{
		switch (type)
		{
		case Hazel::Rigidbody2DType::Static:
			return b2_staticBody;
		case Hazel::Rigidbody2DType::Dynamic:
			return b2_dynamicBody;
		case Hazel::Rigidbody2DType::Kinematic:
			return b2_kinematicBody;
		default:
		{
			LOG_ERROR("Invalid Rigidbody2DType, Failed to cast to b2BodyType, type id is: {0}", (int)type);
			return b2_staticBody;
		}
		}
	}

	b2Shape* CreateB2Shape(const Rigidbody2DShape& shape)
	{
		switch (shape)
		{
		case Rigidbody2DShape::Box:
		{
			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(1.0f, 1.0f);
			return &dynamicBox;
		}
		default:
		{
			return nullptr;
		}
		}
	}

	Rigidbody2D::Rigidbody2D(const float& x, const float& y, 
		const Rigidbody2DType& type, const Rigidbody2DShape& shape) : m_Type(type), m_Shape(shape)
	{
		const std::shared_ptr<b2World>& world = Physics2D::GetWorld();

		if (world == nullptr)
		{
			LOG_ERROR("No World when create Rigidbody2D component");
			return;
		}

		m_BodyDef.position.Set(x, y);
		b2Body* body = world->CreateBody(&m_BodyDef);

		m_BodyDef.type = Rigidbody2DTypeToB2BodyType(type);

		// 添加Fixture(即Collider)
		b2FixtureDef fixtureDef;
		fixtureDef.shape = CreateB2Shape(shape);
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		body->CreateFixture(&fixtureDef);
	}
}