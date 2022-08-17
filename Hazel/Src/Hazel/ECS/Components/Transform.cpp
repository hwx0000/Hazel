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
		glm::mat4 rotationM = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1, 0, 0 }) *
			glm::rotate(glm::mat4(1.0f), Rotation.y, { 0, 1, 0 }) *
			glm::rotate(glm::mat4(1.0f), Rotation.z, { 0, 0, 1 });
		glm::mat4 scaleM = glm::scale(glm::mat4(1.0f), Scale);

		return translationM * rotationM * scaleM;
	}

	void Transform::SetTransformMat(const glm::mat4& trans)
	{
		//Rotation = { 1,0,0 };
		//
		//glm::quat QuatAroundX = glm::quat(Rotation.x, glm::vec3(1.0, 0.0, 0.0));
		//glm::quat QuatAroundY = glm::quat(Rotation.y, glm::vec3(0.0, 1.0, 0.0));
		//glm::quat QuatAroundZ = glm::quat(Rotation.z, glm::vec3(0.0, 0.0, 1.0));
		//glm::quat q = QuatAroundX * QuatAroundY * QuatAroundZ;
		//q = glm::normalize(q);
		

		// TODO: 旋转有问题
		glm::quat q;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(trans, Scale, q, Translation, skew, perspective);
		//q = glm::conjugate(q);
		// https://stackoverflow.com/questions/12048046/quaternions-euler-angles-rotation-matrix-trouble-glm
		// looks like the function 'glm::eulerAngles' returns 'XYZ' as pitch, yaw, and roll.
		Rotation = glm::eulerAngles(q);
	}
}