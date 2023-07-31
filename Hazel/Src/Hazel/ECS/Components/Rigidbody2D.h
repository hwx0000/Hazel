#pragma once
#include "Component.h"
#include "box2d/box2d.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Hazel
{
	enum class Rigidbody2DType
	{
		Static,
		Dynamic,
		Kinematic
	};

	/*
	* Box2D内部的类型为
		e_circle = 0,
		e_edge = 1,
		e_polygon = 2,
		e_chain = 3,
		e_typeCount = 4
	*/

	enum class Rigidbody2DShape
	{
		Box,
		Circle,
		Polygon,
		Line
	};


	class Rigidbody2D : public Component
	{
	public:
		//Rigidbody2D() = delete;
		Rigidbody2D(const float& x = 0.0f, const float& y = 0.0f,
			const Rigidbody2DType& type = Rigidbody2DType::Dynamic, const Rigidbody2DShape & shape = Rigidbody2DShape::Box);

		glm::vec2 GetLocation();
		float GetAngle();

	private:
		b2BodyDef m_BodyDef;
		Rigidbody2DType m_Type;
		Rigidbody2DShape m_Shape;
		b2Body* m_Body;
	};
}