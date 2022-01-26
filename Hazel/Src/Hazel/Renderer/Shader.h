#pragma once
#include "hzpch.h"
#include "glm/glm.hpp"

class Shader
{
public:
	Shader(const std::string& vertSource, const std::string& fragSource);
	~Shader(){} // 未来会有OpenGLShader、DirectXShader，所以未来虚函数可能是virtual的
	void Bind();
	void Unbind();//其实这个函数一般运行时不会用到，一般用于Debug，因为使用的时候会直接Bind新的，就会自动Unbind这个
	void UploadUniformMat4(const std::string& uniformName, glm::mat4 matrix);

private:
	unsigned int m_RendererID;//其实就是program对应的id，program里存放了一套渲染管线的shader
};