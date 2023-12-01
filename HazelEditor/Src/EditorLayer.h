#pragma once
#include "Hazel.h"
#include "Renderer/Framebuffer.h"
#include "ContentBrowserPanel.h"
#include "imgui.h"

namespace Hazel
{
	enum class PlayMode
	{
		Edit,
		Play
	};

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
		void Render();

	private:
		void DrawUIToolbar();
		void EditTransform(float* cameraView, float* cameraProjection, float* matrix, bool editTransformDecomposition);
		void OnScenePlay();
		void OnSceneStop();

	private:

		Hazel::EditorCameraController m_EditorCameraController;
		std::shared_ptr<Hazel::Texture2D> m_Texture2D;
		
		// 专属viewport的framebuffer
		std::shared_ptr<Hazel::Framebuffer> m_ViewportFramebuffer;

		// framebuffer数组, 每个元素对应一个CameraComponent
		std::shared_ptr<Hazel::Framebuffer> m_CameraComponentFramebuffer;
		std::shared_ptr<Hazel::Scene> m_EditorScene;
		std::shared_ptr<Hazel::Scene> m_RuntimeScene;// Used in Play Mode
		std::shared_ptr<Hazel::Scene> m_ActiveScene;

		glm::vec4 m_FlatColor = glm::vec4(0.2, 0.3, 0.8, 1.0);
		glm::vec2 m_LastViewportSize = { 800, 600 };
		//glm::vec2 m_HoverPosInViewport = { 0, 0 };// Hover Position in viewport window

		glm::vec2 m_ViewportMin = { 0, 0 };
		glm::vec2 m_ViewportMax = { 0, 0 };

		// 添加一个数组, 每个数组元素代表每个Timer的结果
		std::vector<Hazel::ProfileResult> m_ProfileResults;

		bool m_ViewportFocused;
		bool m_ViewportHovered;

		bool m_ShowCameraComponent = false;
		bool m_EnableMSAATex = true;

		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;

		enum class ToolbarOptions
		{
			Default,
			Translate,
			Rotation,
			Scale
		};

		ToolbarOptions m_Option = ToolbarOptions::Translate;

		PlayMode m_PlayMode = PlayMode::Edit;

		std::shared_ptr<Texture2D> m_IconPlay;
		std::shared_ptr<Texture2D> m_IconStop;
	};
}