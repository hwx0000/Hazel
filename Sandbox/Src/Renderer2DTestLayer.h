#pragma once
#include "Hazel.h"

class Renderer2DTestLayer : public Hazel::Layer
{
public:
	Renderer2DTestLayer(const std::string& name = "Layer");
	~Renderer2DTestLayer();
	void OnAttach() override; //当layer添加到layer stack的时候会调用此函数，相当于Init函数
	void OnDettach() override; //当layer从layer stack移除的时候会调用此函数，相当于Shutdown函数
	void OnEvent(Hazel::Event&) override;
	void OnUpdate(const Hazel::Timestep&) override;
	void OnImGuiRender() override;

private:
	Hazel::OrthographicCameraController m_OrthoCameraController;
	std::shared_ptr<Hazel::Texture2D> m_Texture2D;

	glm::vec4 m_FlatColor = glm::vec4(0.2, 0.3, 0.8, 1.0);
};