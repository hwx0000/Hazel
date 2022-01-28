#include "Hazel.h"
#include "../imgui/imgui.h"

class ExampleLayer : public Hazel::Layer
{
	void OnAttach() override
	{
		CORE_LOG("Init Layer");
	}

	void OnDettach() override
	{
		CORE_LOG("Close Layer");
	}

	void OnEvent(Hazel::Event& e) override
	{
		//if (e.GetEventType() == Hazel::EventType::KeyPressed)
		//{
		//	Hazel::KeyPressedEvent* ep = dynamic_cast<Hazel::KeyPressedEvent*>(&e);
		//	LOG("{0}{1}", (char)ep->GetKeycode(), "Is Pressed");
		//}
		//LOG("{0}", s);
		//LOG("{0}", s);
		//LOG("{0}", "SampleLayer: ");//, e.ToString());
	}

	void OnUpdate() override
	{




		//CORE_LOG("{0}{1}", "Is Key Pressed :", Hazel::Input::IsKeyPressed(HZ_KEY_K));
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		m_LayerStack.PushLayer(new ExampleLayer());
	};
	~Sandbox(){};
private:
};

Hazel::Application* Hazel::CreateApplication() 
{
	Sandbox *s = new Sandbox();
	return s;
}
