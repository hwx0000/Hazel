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

	b2PolygonShape CreateB2Shape(const Rigidbody2DShape& shape)
	{
		switch (shape)
		{
		case Rigidbody2DShape::Box:
		{
			// TODO: 这里是否会有问题?
			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(0.5f, 0.5f);// 对应1m*1m的Box
			return dynamicBox;
		}
		default:
		{
			b2PolygonShape dynamicBox;
			return dynamicBox;
		}
		}
	}

	Rigidbody2D::Rigidbody2D(const float& x, const float& y, 
		const Rigidbody2DType& type, const Rigidbody2DShape& shape) : m_Pos(x, y), m_Type(type), m_Shape(shape)
	{
		// TODO: 准确的说, 这部分内容不应该在AddComponent时调用, 而应该在PlayMode下调用
		Init();
	}

	void Rigidbody2D::Init()
	{
		const std::shared_ptr<b2World>& world = Physics2D::GetWorld();

		if (world == nullptr)
		{
			LOG_ERROR("No World when create Rigidbody2D component");
			return;
		}

		// 注意, 调用CreateBody之前要把b2BodyDef里的参数都填好
		m_BodyDef.position.Set(m_Pos.x, m_Pos.y);
		m_BodyDef.type = Rigidbody2DTypeToB2BodyType(m_Type);
		m_Body = world->CreateBody(&m_BodyDef);


		// 添加Fixture(即Collider)
		b2FixtureDef fixtureDef;
		b2PolygonShape dynamicBox = CreateB2Shape(m_Shape);
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		m_Body->CreateFixture(&fixtureDef);
	}

	glm::vec2 Rigidbody2D::GetLocation()
	{
		if (m_Body)
			return glm::vec2(m_Body->GetPosition().x, m_Body->GetPosition().y);

		return { 0,0 };
	}
	

	float Rigidbody2D::GetAngle()
	{
		if (m_Body)
			return m_Body->GetAngle();

		return 0;
	}

	void Rigidbody2D::SetType(const Rigidbody2DType& type)
	{
		if (m_Body)
		{
			m_Type = type;
			m_Body->SetType(Rigidbody2DTypeToB2BodyType(type));
		}
	}
}