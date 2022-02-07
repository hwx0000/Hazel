#pragma once
#include "Hazel/Layer.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/OrthographicCamera.h"

// 这里的Camera是属于Layer的, 没有存在Application或Sandbox类里
class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer();

private:
	void OnAttach() override;
	void OnDettach() override;
	void OnEvent(Hazel::Event& e) override;
	void OnUpdate(const Timestep& step) override;
	void OnImGuiRender() override;

private:
	Hazel::OrthographicCamera m_Camera;
	std::shared_ptr<Hazel::Shader> m_TriangleShader;
	std::shared_ptr<Hazel::Shader> m_FlatColorShader;

	std::shared_ptr<Hazel::VertexArray> m_TriangleVertexArray;
	std::shared_ptr<Hazel::VertexArray> m_QuadVertexArray;
	glm::vec4 m_FlatColor = glm::vec4(0.2, 0.3, 0.8, 1.0);
};