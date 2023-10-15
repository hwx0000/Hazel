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
		Rigidbody2D(const float& x, const float& y, const float& angle,
			const Rigidbody2DType& type = Rigidbody2DType::Dynamic, const Rigidbody2DShape& shape = Rigidbody2DShape::Box);

		glm::vec2 GetLocation();
		glm::vec2& GetExtents() { return m_Extents; }
		void SetExtents(const glm::vec2&);
		float GetAngle();

		Rigidbody2DType GetType() { return m_Type; }
		void SetType(const Rigidbody2DType&);

	protected:
		void Init();


	private:
		b2BodyDef m_BodyDef;
		Rigidbody2DType m_Type;
		Rigidbody2DShape m_Shape;
		b2Body* m_Body = nullptr;

		glm::vec2 m_Pos;
		glm::vec2 m_Extents;
		float m_Angle = 0.0f;
	};
}