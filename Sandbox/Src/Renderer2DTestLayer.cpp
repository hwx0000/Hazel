#include "Renderer2DTestLayer.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer/Renderer2D.h"
#include <filesystem>

Renderer2DTestLayer::Renderer2DTestLayer(const std::string& name) :
m_OrthoCameraController(1.6667f, 1.0f)
{
	//m_ShaderLibrary = std::make_shared<Hazel::ShaderLibrary>();
	//// std::filesystem是C++17提供的库, 用于方便的获取Project的绝对路径
	//std::string path = std::filesystem::current_path().string();
	//std::string shaderPath1 = std::filesystem::current_path().string() + "\\Resources\\TextureShader.glsl";
	//m_ShaderLibrary->Load(shaderPath1);

	//auto m_TextureShader = m_ShaderLibrary->Get("TextureShader");

	//std::string path1 = path + "\\Resources\\HeadIcon.jpg";

	Hazel::Renderer2D::Init();
}

Renderer2DTestLayer::~Renderer2DTestLayer()
{
	Hazel::Renderer2D::Shutdown();
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

	// 每帧开始Clear
	Hazel::RenderCommand::Clear();
	Hazel::RenderCommand::ClearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	Hazel::Renderer2D::BeginScene(m_OrthoCameraController.GetCamera());
	{
		Hazel::Renderer2D::DrawQuad({ 0,0,0 }, { 1,1 }, { 1.0f,0.0f,1.0f,1.0f });
	}
	Hazel::Renderer2D::EndScene();
}

void Renderer2DTestLayer::OnImGuiRender()
{
	ImGui::Begin("Test");
	ImGui::Text("Hello World");
	ImGui::ColorEdit4("Flat Color Picker", glm::value_ptr(m_FlatColor));
	ImGui::End();
}