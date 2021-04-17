#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Event/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		inline static Application& Get() { return *s_Instance;  }

		void OnEvent(Event& e);
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		void PushLayer(Layer* layer);
		Layer* PopLayer();
		Window& GetWindow()const { return *m_Window; }
	private:
		static Application* s_Instance;
	protected:
		std::unique_ptr<Window>m_Window;
		std::unique_ptr<Shader>m_Shader;
		std::unique_ptr<Shader>m_BlueShader;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;

		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexArray> m_QuadVertexArray;
	};

	Application* CreateApplication();
}