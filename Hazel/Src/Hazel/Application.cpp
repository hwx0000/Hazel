#include "hzpch.h"
#include "Application.h"
#include "Window.h"
#include "Event/MouseEvent.h"
#include "Event/ApplicationEvent.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Input.h"
#include "Renderer/Buffer.h"

namespace Hazel
{
	Application* Application::s_Instance = nullptr;
	int indices[3] = { 0,1,2 };

	Application::Application()
	{
		HAZEL_ASSERT(!s_Instance, "Already Exists an application instance");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		//m_Window->SetEventCallback([](Event& e)->void
		//{
		//	if (e.GetEventType() == EventType::MouseScrolled)
		//	{
		//		MouseScrolledEvent ee = (MouseScrolledEvent&)e;
		//		LOG( "xOffset:{0} and yOffset:{1}", ee.GetXOffset(), ee.GetYOffset());
		//	}
		//}
		//);
		m_ImGuiLayer = new ImGuiLayer();
		m_LayerStack.PushOverlay(m_ImGuiLayer);
		

		float vertices[3 * 3] = {
			-0.5, -0.5, 0,
			0.5, -0.5, 0,
			0, 0.5, 0
		};

		buffer = VertexBuffer::Create(vertices, sizeof(vertices));
		buffer->Bind();

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//��CPU������GPU

		std::string vertexSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
void main()
{
	gl_Position = vec4(aPos, 1.0);
}
		)";

		std::string fragmentSource = R"(
#version 330 core
out vec4 color;
void main()
{
	color = vec4(0.8,0.2,0.3,1.0);
}
		)";
		m_Shader.reset(new Shader(vertexSource, fragmentSource));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		for (Layer* layer : m_LayerStack)
		{
			layer->OnEvent(e);
		}
	}


	void Application::Run() 
	{
		std::cout << "Run Application" << std::endl;
		while (m_Running)
		{
			// ÿ֡��ʼClear
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			buffer->Bind();

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			// Application����Ӧ��֪�����õ����ĸ�ƽ̨��window��Window��init��������Window::Create����
			// ���Դ�����window�󣬿���ֱ�ӵ�����loop��ʼ��Ⱦ
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				// ÿһ��Layer���ڵ���ImGuiRender����
				// Ŀǰ������Layer, Sandbox�����ExampleLayer�͹��캯����ӵ�ImGuiLayer
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			
			// ÿ֡��������glSwapBuffer
			m_Window->OnUpdate();
			//LOG("{0}{1}", "Is Key K Pressed", Input::IsKeyPressed(75));
		}

		//LOG(w.ToString());
	}

	bool Application::OnWindowClose(WindowCloseEvent &e)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer * layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	Layer* Application::PopLayer()
	{
		return m_LayerStack.PopLayer();
	}
}