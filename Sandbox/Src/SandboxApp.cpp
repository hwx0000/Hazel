#include "Hazel.h"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}


class ExampleLayer : public Hazel::Layer
{
	void OnAttach() override
	{
		glm::vec2 a(1.0f, 20.0f);
		camera(1.0f, a);
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
		m_LayerStack.PushOverlay(new Hazel::ImGuiLayer());
	};
	~Sandbox(){};
private:
};

Hazel::Application* Hazel::CreateApplication() 
{
	Sandbox *s = new Sandbox();
	return s;
}
