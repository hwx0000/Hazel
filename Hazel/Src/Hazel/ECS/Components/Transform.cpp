#include "hzpch.h"
#include "Transform.h"
#include "glm/gtx/transform.hpp"

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
}