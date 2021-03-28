#pragma once
#include "hzpch.h"

class Shader
{
public:
	Shader(const std::string& vertSource, const std::string& fragSource);
	~Shader(){} // δ������OpenGLShader��DirectXShader������δ���麯��������virtual��
	void Bind();
	void Unbind();//��ʵ�������һ������ʱ�����õ���һ������Debug����Ϊʹ�õ�ʱ���ֱ��Bind�µģ��ͻ��Զ�Unbind���
private:
	unsigned int m_RendererID;//��ʵ����program��Ӧ��id��program������һ����Ⱦ���ߵ�shader
};