#pragma once
#include "Hazel.h"
#include "Renderer/Framebuffer.h"

namespace Hazel
{
	class EditorLayer : public Hazel::Layer
	{
	public:
		EditorLayer(const std::string& name = "Layer");
		~EditorLayer();
		void OnAttach() override; //当layer添加到layer stack的时候会调用此函数，相当于Init函数
		void OnDetach() override; //当layer从layer stack移除的时候会调用此函数，相当于Shutdown函数
		void OnEvent(Hazel::Event&) override;
		void OnUpdate(const Hazel::Timestep&) override;
		void OnImGuiRender() override;

	private:
		Hazel::OrthographicCameraController m_OrthoCameraController;
		std::shared_ptr<Hazel::Texture2D> m_Texture2D;
		std::shared_ptr<Hazel::Framebuffer> m_Framebuffer;
		std::shared_ptr<Hazel::Scene> m_Scene;

		glm::vec4 m_FlatColor = glm::vec4(0.2, 0.3, 0.8, 1.0);
		glm::vec2 m_LastViewportSize = { 0, 0 };

		// 添加一个数组, 每个数组元素代表每个Timer的结果
		std::vector<Hazel::ProfileResult> m_ProfileResults;

		bool m_ViewportFocused;
		bool m_ViewportHovered;
	};
}