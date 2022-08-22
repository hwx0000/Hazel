#include "hzpch.h"
#include "Transform.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/quaternion.hpp"

namespace Hazel
{
	glm::mat4 Transform::GetTransformMat()
	{
		glm::mat4 translationM = glm::translate(Translation);

		// Order: XYZ
		glm::mat4 rotationM = glm::rotate(glm::mat4(1.0f), Rotation.z, { 0, 0, 1 }) *
			glm::rotate(glm::mat4(1.0f), Rotation.y, { 0, 1, 0 }) *
			glm::rotate(glm::mat4(1.0f), Rotation.x, { 1, 0, 0 });
		glm::mat4 scaleM = glm::scale(glm::mat4(1.0f), Scale);

		return translationM * rotationM * scaleM;
	}

	void Transform::SetTransformMat(const glm::mat4& trans)
	{
		glm::quat q;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(trans, Scale, q, Translation, skew, perspective);

		auto qXYZ = glm::eulerAngles(q);// XYZ的顺序
		Rotation.x = qXYZ.x;
		Rotation.y = qXYZ.y;
		Rotation.z = qXYZ.z;
	}
}