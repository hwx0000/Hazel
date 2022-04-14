#include "SandboxApp.h"
#include "ExampleLayer.h"
#include "Renderer2DTestLayer.h"


HazelEditorApp::HazelEditorApp()
{
	HAZEL_ASSERT(!s_Instance, "Already Exists an application instance");

	m_Window = std::unique_ptr<Hazel::Window>(Hazel::Window::Create());
	m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

	m_ImGuiLayer = new Hazel::ImGuiLayer();
	m_LayerStack.PushOverlay(m_ImGuiLayer);
	
	//m_LayerStack.PushLayer(new ExampleLayer());
	m_LayerStack.PushLayer(new Renderer2DTestLayer());

	//m_Window->SetVSync(true);
}

Hazel::Application* Hazel::CreateApplication() 
{
	HazelEditorApp *s = new HazelEditorApp();
	return s;
}
