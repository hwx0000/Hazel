#include "../imgui/imgui.h"
#include "SandboxApp.h"

int indices[3] = { 0,1,2 };

Sandbox::Sandbox()
{
	HAZEL_ASSERT(!s_Instance, "Already Exists an application instance");

	m_Window = std::unique_ptr<Hazel::Window>(Hazel::Window::Create());
	m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

	m_ImGuiLayer = new Hazel::ImGuiLayer();
	m_LayerStack.PushOverlay(m_ImGuiLayer);

	float vertices[] =
	{
		-0.5, -0.5, 0, 1.0, 0.0, 0.0, 1.0f,
		0.5, -0.5, 0, 0.0, 1.0, 0.0, 1.0f,
		0, 0.5, 0.0, 0.0, 0.0, 1.0, 1.0f
	};

	// 创建VBO
	std::shared_ptr<Hazel::VertexBuffer>m_VertexBuffer = std::shared_ptr<Hazel::VertexBuffer>(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
	m_VertexBuffer->Bind();

	// 创建Layout，会计算好Stride和Offset
	Hazel::BufferLayout layout = {
		{Hazel::ShaderDataType::FLOAT3, "a_Pos" },
		{Hazel::ShaderDataType::FLOAT4, "a_Color" }
	};

	m_VertexBuffer->SetBufferLayout(layout);

	// 创建Vertex Array，把前面算好的东西传入VAO
	m_VertexArray.reset(Hazel::VertexArray::Create());
	m_VertexArray->Bind();
	m_VertexArray->AddVertexBuffer(m_VertexBuffer);

	std::shared_ptr<Hazel::IndexBuffer> m_IndexBuffer = 
		std::shared_ptr<Hazel::IndexBuffer>(Hazel::IndexBuffer::Create(indices, sizeof(indices)));
	m_IndexBuffer->Bind();
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);

	std::string vertexSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

uniform mat4 m_ViewProjection;

out vec4 o_color;
void main()
{
	gl_Position = m_ViewProjection * vec4(aPos, 1.0);
	o_color = aColor;
}
		)";

	std::string fragmentSource = R"(
#version 330 core
in vec4 o_color;
out vec4 color;
void main()
{
	color = o_color;
}
		)";
	m_Shader.reset(new Shader(vertexSource, fragmentSource));

	float quadVertices[] = {
		-0.75f, -0.75f, 0,
		0.75f, -0.75f,0,
		-0.75f, 0.75f,0,
		0.75f, 0.75f, 0
	};

	int quadIndices[] = { 0,1,2,2,1,3 };

	// 创建Vertex Array，把前面算好的东西传入VAO
	m_QuadVertexArray.reset(Hazel::VertexArray::Create());

	std::shared_ptr<Hazel::VertexBuffer> quadVertexBufer;
	quadVertexBufer.reset(Hazel::VertexBuffer::Create(quadVertices, sizeof(quadVertices)));

	quadVertexBufer->SetBufferLayout(
		{
			{Hazel::ShaderDataType::FLOAT3, "aPos"}
		});
	m_QuadVertexArray->AddVertexBuffer(quadVertexBufer);

	std::shared_ptr<Hazel::IndexBuffer> quadIndexBufer;
	quadIndexBufer = std::unique_ptr<Hazel::IndexBuffer>(Hazel::IndexBuffer::Create(quadIndices, sizeof(quadIndices)));
	quadIndexBufer->Bind();
	m_QuadVertexArray->SetIndexBuffer(quadIndexBufer);

	std::string blueVertexSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 u_ViewProjection;

void main()
{
	gl_Position = u_ViewProjection * vec4(aPos, 1.0);
}
		)";

	std::string blueFragmentSource = R"(
#version 330 core
out vec4 color;

void main()
{
	color = vec4(0.2, 0.3, 0.8, 1.0);
}
		)";
	m_BlueShader.reset(new Shader(blueVertexSource, blueFragmentSource));

	m_Camera.reset(new Hazel::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f));

	m_LayerStack.PushLayer(new ExampleLayer());
}

void Sandbox::Run()
{
	while (m_Running)
	{
		auto m_CameraPosition = m_Camera->GetPosition();
		auto m_CameraRotation = m_Camera->GetRotation();
		float m_CameraMoveSpeed = 0.01f;
		float m_CameraRotationSpeed = 1.0f;

		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;

		// 由于是2D的Camera, 用一个绕Z轴的角度表示相机旋转即可
		if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;
		if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;

		m_Camera->SetPosition(m_CameraPosition);
		m_Camera->SetRotation(m_CameraRotation);

		// 1. 先执行引擎内部的循环逻辑
		// 每帧开始Clear
		Hazel::RenderCommand::Clear();
		Hazel::RenderCommand::ClearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

		// 把Camera里的VP矩阵信息传到Renderer的SceneData里
		Hazel::Renderer::BeginScene(*m_Camera);
		{
			// todo: 后续操作应该有Batch
			// bind shader, 然后Upload VP矩阵到unifor,, 然后调用DrawCall
			Hazel::Renderer::Submit(m_BlueShader, m_VertexArray);
			// bind shader, 然后Upload VP矩阵到unifor,, 然后调用DrawCall
			Hazel::Renderer::Submit(m_Shader, m_QuadVertexArray);
		}
		Hazel::Renderer::EndScene();

		// 2. 再执行使用引擎的用户代码的循环
		// Application并不应该知道调用的是哪个平台的window，Window的init操作放在Window::Create里面
		// 所以创建完window后，可以直接调用其loop开始渲染
		for (Hazel::Layer* layer : m_LayerStack)
		{
			layer->OnUpdate();
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
	}
}


Hazel::Application* Hazel::CreateApplication() 
{
	Sandbox *s = new Sandbox();
	return s;
}
