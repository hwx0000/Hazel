#include "hzpch.h"
#include "Transform.h"
#include "glm/gtx/transform.hpp"
#include <glm/gtx/matrix_decompose.hpp>

namespace Hazel
{
	glm::mat4 Transform::GetTransformMat()
	{
		glm::mat4 translationM = glm::translate(Translation);
		glm::mat4 rotationM = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1, 0, 0 }) *
			glm::rotate(glm::mat4(1.0f), Rotation.y, { 0, 1, 0 }) *
			glm::rotate(glm::mat4(1.0f), Rotation.z, { 0, 0, 1 });
		glm::mat4 scaleM = glm::scale(glm::mat4(1.0f), Scale);

		return translationM * rotationM * scaleM;
	}

	void Transform::SetTransformMat(const glm::mat4& trans)
	{
		glm::quat quat;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(trans, Scale, quat, Translation, skew, perspective);

		// https://stackoverflow.com/questions/12048046/quaternions-euler-angles-rotation-matrix-trouble-glm
		// looks like the function 'glm::eulerAngles' returns 'XYZ' as pitch, yaw, and roll.
		Rotation = glm::eulerAngles(quat) * 3.14159f / 180.f;
	}
}