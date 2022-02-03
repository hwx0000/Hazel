#include "SandboxApp.h"
#include "ExampleLayer.h"


SandboxApp::SandboxApp()
{
	HAZEL_ASSERT(!s_Instance, "Already Exists an application instance");

	m_Window = std::unique_ptr<Hazel::Window>(Hazel::Window::Create());
	m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

	m_ImGuiLayer = new Hazel::ImGuiLayer();
	m_LayerStack.PushOverlay(m_ImGuiLayer);
	
	m_LayerStack.PushLayer(new ExampleLayer());
}

void SandboxApp::Run()
{
	while (m_Running)
	{
		// 2. 再执行使用引擎的用户代码的循环
		// Application并不应该知道调用的是哪个平台的window，Window的init操作放在Window::Create里面
		// 所以创建完window后，可以直接调用其loop开始渲染
		for (Hazel::Layer* layer : m_LayerStack)
		{
			layer->OnUpdate(m_Timestep);
		}

		// 3. 最后调用ImGUI的循环
		m_ImGuiLayer->Begin();
		for (Hazel::Layer* layer : m_LayerStack)
		{
			// 每一个Layer都在调用ImGuiRender函数
			// 目前有两个Layer, Sandbox定义的ExampleLayer和构造函数添加的ImGuiLayer
			layer->OnImGuiRender();
		}
		m_ImGuiLayer->End();

		// 4. 每帧结束调用glSwapBuffer函数, 把画面显示到屏幕上
		m_Window->OnUpdate();

		//m_LastTimestep = ;
	}
}


Hazel::Application* Hazel::CreateApplication() 
{
	SandboxApp *s = new SandboxApp();
	return s;
}
