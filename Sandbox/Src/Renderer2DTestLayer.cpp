#include "Renderer2DTestLayer.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <filesystem>

Renderer2DTestLayer::Renderer2DTestLayer(const std::string& name) :
m_OrthoCameraController(1.6667f, 1.0f)
{
	float quadVertices[] =
	{
		-0.5f, -0.5f, 0, 0.0f, 0.0f,
		 0.5f, -0.5f, 0, 1.0f, 0.0f,
		-0.5f,  0.5f, 0, 0.0f, 1.0f,
		 0.5f,  0.5f, 0, 1.0f, 1.0f
	};

	int quadIndices[] = { 0,1,2,2,1,3 };

	// 创建VBO
	std::shared_ptr<Hazel::VertexBuffer>m_QuadVertexBuffer =
		std::shared_ptr<Hazel::VertexBuffer>(Hazel::VertexBuffer::Create(quadVertices, sizeof(quadVertices)));
	m_QuadVertexBuffer->Bind();

	// 创建Layout，会计算好Stride和Offset
	Hazel::BufferLayout layout =
	{
		{ Hazel::ShaderDataType::FLOAT3, "a_Pos" },
		{ Hazel::ShaderDataType::FLOAT2, "a_Tex" }
	};

	m_QuadVertexBuffer->SetBufferLayout(layout);

	// 创建Vertex Array，把前面算好的东西传入VAO
	// VAO从VBO里挖取数据
	m_QuadVertexArray.reset(Hazel::VertexArray::Create());
	m_QuadVertexArray->Bind();
	m_QuadVertexArray->AddVertexBuffer(m_QuadVertexBuffer);

	std::shared_ptr<Hazel::IndexBuffer> m_QuadIndexBuffer =
		std::shared_ptr<Hazel::IndexBuffer>(Hazel::IndexBuffer::Create(quadIndices, sizeof(quadIndices)));
	m_QuadIndexBuffer->Bind();
	m_QuadVertexArray->SetIndexBuffer(m_QuadIndexBuffer);

	m_ShaderLibrary = std::make_shared<Hazel::ShaderLibrary>();
	// std::filesystem是C++17提供的库, 用于方便的获取Project的绝对路径
	std::string path = std::filesystem::current_path().string();
	std::string shaderPath1 = std::filesystem::current_path().string() + "\\Resources\\TextureShader.glsl";
	m_ShaderLibrary->Load(shaderPath1);

	auto m_TextureShader = m_ShaderLibrary->Get("TextureShader");

	std::string path1 = path + "\\Resources\\HeadIcon.jpg";
	m_Texture = Hazel::Texture2D::Create(path1);
}

Renderer2DTestLayer::~Renderer2DTestLayer()
{
}

void Renderer2DTestLayer::OnAttach()
{
	CORE_LOG("Init Layer");
}

void Renderer2DTestLayer::OnDettach()
{
	CORE_LOG("Detach Layer");
}

void Renderer2DTestLayer::OnEvent(Hazel::Event& e )
{
	m_OrthoCameraController.OnEvent(e);
}

void Renderer2DTestLayer::OnUpdate(const Hazel::Timestep& ts)
{
	m_OrthoCameraController.OnUpdate(ts);

	// 1. 先执行引擎内部的循环逻辑
	// 每帧开始Clear
	Hazel::RenderCommand::Clear();
	Hazel::RenderCommand::ClearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	auto& textureShader = m_ShaderLibrary->Get("TextureShader");

	Hazel::Renderer::BeginScene(m_OrthoCameraController.GetCamera());
	{
		glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
		m_Texture->Bind(0);
		Hazel::Renderer::Submit(textureShader, m_QuadVertexArray, transform);
	}
	Hazel::Renderer::EndScene();
}

void Renderer2DTestLayer::OnImGuiRender()
{
	ImGui::Begin("Test");
	ImGui::Text("Hello World");
	ImGui::ColorEdit4("Flat Color Picker", glm::value_ptr(m_FlatColor));
	ImGui::End();
}