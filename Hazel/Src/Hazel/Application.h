#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Event/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Renderer.h"

namespace Hazel
{
	// Application类是Hazel引擎提供给外部使用引擎的接口类, 这里声明了一个全局函数
	// Application* CreateApplication(); 但是没有定义它
	// 会留给使用引擎的用户来定义这个函数, 返回对应用户自定义的继承Application的类对象
	// 在main函数里, 会调用：
	// auto app = Hazel::CreateApplication();
	// app->Run();
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