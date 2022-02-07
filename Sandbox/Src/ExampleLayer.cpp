#include "ExampleLayer.h"
#include "Hazel/Input.h"
#include "Hazel/Renderer/RenderCommand.h"
#include "Hazel/Renderer/RendererAPI.h"
#include "Hazel/Renderer/Renderer.h"
#include "Hazel//KeyCode.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>


ExampleLayer::ExampleLayer() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
	float triangleVertices[] =
	{
		-0.5, -0.5, 0, 1.0, 0.0, 0.0, 1.0f,
		0.5, -0.5, 0, 0.0, 1.0, 0.0, 1.0f,
		0, 0.5, 0.0, 0.0, 0.0, 1.0, 1.0f
	};

	// 创建VBO
	std::shared_ptr<Hazel::VertexBuffer>m_TriangleVertexBuffer = std::shared_ptr<Hazel::VertexBuffer>(Hazel::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
	m_TriangleVertexBuffer->Bind();

	// 创建Layout，会计算好Stride和Offset
	Hazel::BufferLayout layout = 
	{
		{Hazel::ShaderDataType::FLOAT3, "a_Pos" },
		{Hazel::ShaderDataType::FLOAT4, "a_Color" }
	};

	m_TriangleVertexBuffer->SetBufferLayout(layout);

	// 创建Vertex Array，把前面算好的东西传入VAO
	m_TriangleVertexArray.reset(Hazel::VertexArray::Create());
	m_TriangleVertexArray->Bind();
	m_TriangleVertexArray->AddVertexBuffer(m_TriangleVertexBuffer);

	int triangleIndices[3] = { 0,1,2 };

	std::shared_ptr<Hazel::IndexBuffer> m_TriangleIndexBuffer =
		std::shared_ptr<Hazel::IndexBuffer>(Hazel::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices)));
	m_TriangleIndexBuffer->Bind();
	m_TriangleVertexArray->SetIndexBuffer(m_TriangleIndexBuffer);

	std::string vertexSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

out vec4 o_color;
void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0);
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
	m_TriangleShader.reset(Hazel::Shader::Create(vertexSource, fragmentSource));

	float quadVertices[] = 
	{
		-0.5f, -0.5f, 0,
		0.5f, -0.5f,0,
		-0.5f, 0.5f,0,
		0.5f, 0.5f, 0
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

	std::string flatShaderVertexSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0);
}
		)";

	std::string flatShaderFragmentSource = R"(
#version 330 core
out vec4 color;

uniform vec4 u_Color;

void main()
{
	color = u_Color;
}
		)";

	m_FlatColorShader.reset(Hazel::Shader::Create(flatShaderVertexSource, flatShaderFragmentSource));
}

void ExampleLayer::OnAttach()
{
	CORE_LOG("Init Layer");
}

void ExampleLayer::OnDettach()
{
	CORE_LOG("Close Layer");
}

void ExampleLayer::OnEvent(Hazel::Event & e)
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

// 这里的step相当于deltaTime
void ExampleLayer::OnUpdate(const Timestep & step)
{
	auto m_CameraPosition = m_Camera.GetPosition();
	auto m_CameraRotation = m_Camera.GetRotation();
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotationSpeed = 10.0f;

	if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
		m_CameraPosition.x -= m_CameraMoveSpeed * step;
	else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
		m_CameraPosition.x += m_CameraMoveSpeed * step;

	if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
		m_CameraPosition.y += m_CameraMoveSpeed * step;
	else if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
		m_CameraPosition.y -= m_CameraMoveSpeed * step;

	// 由于是2D的Camera, 用一个绕Z轴的角度表示相机旋转即可
	if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
		m_CameraRotation += m_CameraRotationSpeed * step;
	if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
		m_CameraRotation -= m_CameraRotationSpeed * step;

	m_Camera.SetPosition(m_CameraPosition);
	m_Camera.SetRotation(m_CameraRotation);


	// 1. 先执行引擎内部的循环逻辑
	// 每帧开始Clear
	Hazel::RenderCommand::Clear();
	Hazel::RenderCommand::ClearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	// 把Camera里的VP矩阵信息传到Renderer的SceneData里
	Hazel::Renderer::BeginScene(m_Camera);
	{
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_FlatColorShader->Bind();
		m_FlatColorShader->UploadUniformVec4("u_Color", m_FlatColor);

		// 绘制400个quad, 每个的size为0.1, 屏幕是-1到1, 也就是20分之一的屏幕
		for (int x = -20; x < 20; x++)
		{
			for (int y = -20; y < 20; y++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				// bind shader, 然后Upload VP矩阵到uniform, 然后调用DrawCall
				Hazel::Renderer::Submit(m_FlatColorShader, m_QuadVertexArray, transform);
			}
		}

		// todo: 后续操作应该有Batch
	}
	Hazel::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Test");
	ImGui::Text("Hello World");
	ImGui::ColorEdit4("Flat Color Picker", glm::value_ptr(m_FlatColor));
	ImGui::End();
}
