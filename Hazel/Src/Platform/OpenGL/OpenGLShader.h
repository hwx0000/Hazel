#pragma once
#include "Hazel/Renderer/Shader.h"


namespace Hazel
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertSource, const std::string& fragSource);
		void Bind() override;
		void Unbind() override;//其实这个函数一般运行时不会用到，一般用于Debug，因为使用的时候会直接Bind新的，就会自动Unbind这个
		void UploadUniformMat4(const std::string& uniformName, glm::mat4 matrix) override;
		void UploadUniformVec4(const std::string& uniformName, glm::vec4 vec4) override;
		void UploadUniformI1(const std::string& uniformName, int id) override;
	};
}