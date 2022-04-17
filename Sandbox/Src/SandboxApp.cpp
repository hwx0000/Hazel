#include "SandboxApp.h"
#include "ExampleLayer.h"
#include "Renderer2DTestLayer.h"


HazelEditorApp::HazelEditorApp()
{
	HAZEL_ASSERT(!s_Instance, "Already Exists an application instance");

	m_LayerStack.PushLayer(std::make_shared<Renderer2DTestLayer>());

	//m_Window->SetVSync(true);
}

Hazel::Application* Hazel::CreateApplication() 
{
	HazelEditorApp *s = new HazelEditorApp();
	return s;
}
