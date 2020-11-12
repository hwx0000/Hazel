#include "Hazel.h"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi


class ExampleLayer : public Hazel::Layer
{
	void OnAttach() override
	{
		LOG("Init Layer");
	}

	void OnDettach() override
	{
		LOG("Close Layer");
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
		LOG("{0}{1}", "Is Key Pressed :", Hazel::Input::IsKeyPressed(HZ_KEY_K));
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
