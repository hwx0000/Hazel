#include "HazelEditorApp.h"
#include "EditorLayer.h"


HazelEditorApp::HazelEditorApp()
{
	HAZEL_ASSERT(!s_Instance, "Already Exists an application instance");
	
	m_LayerStack.PushLayer(new EditorLayer());

	//m_Window->SetVSync(true);
}

Hazel::Application* Hazel::CreateApplication() 
{
	HazelEditorApp *s = new HazelEditorApp();
	return s;
}
