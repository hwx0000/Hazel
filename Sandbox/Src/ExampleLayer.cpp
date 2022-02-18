#include "ExampleLayer.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <filesystem>

ExampleLayer::ExampleLayer() : m_OrthoCameraController(1.6667f, 1.0f)
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
	// 这玩意儿是C++17提供的库, 用于方便的获取Project的绝对路径
	std::string path = std::filesystem::current_path().string();
	std::string shaderPath1 = std::filesystem::current_path().string() + "\\Resources\\TextureShader.glsl";
	m_ShaderLibrary->Load(shaderPath1);
	
	auto m_TextureShader = m_ShaderLibrary->Get("TextureShader");

	// 两个Shader共享VAO, VBO和EBO
	// std::filesystem是C++17提供的库, 用于方便的获取Project的绝对路径
	std::string shaderPath2 = std::filesystem::current_path().string() + "\\Resources\\FlatColorShader.glsl";
	m_ShaderLibrary->Load(shaderPath2);
	auto m_FlatColorShader = m_ShaderLibrary->Get("FlatColorShader");

	
	std::string path1 = path + "\\Resources\\HeadIcon.jpg";
	m_TextureOne = Hazel::Texture2D::Create(path1);

	std::string path2 = path + "\\Resources\\RedSquare.png";
	m_TextureTwo = Hazel::Texture2D::Create(path2);
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
	m_OrthoCameraController.OnEvent(e);
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
void ExampleLayer::OnUpdate(const Hazel::Timestep & step)
{
	m_OrthoCameraController.OnUpdate(step);

	// 1. 先执行引擎内部的循环逻辑
	// 每帧开始Clear
	Hazel::RenderCommand::Clear();
	Hazel::RenderCommand::ClearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	auto flatColorShader = m_ShaderLibrary->Get("FlatColorShader");
	auto textureShader = m_ShaderLibrary->Get("TextureShader");

	// 把Camera里的VP矩阵信息传到Renderer的SceneData里
	Hazel::Renderer::BeginScene(m_OrthoCameraController.GetCamera());
	{
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		
		flatColorShader->Bind();
		flatColorShader->UploadUniformVec4("u_Color", m_FlatColor);

		// 绘制400个quad, 每个的size为0.1, 屏幕是-1到1, 也就是20分之一的屏幕
		for (int x = -20; x < 20; x++)
		{
			for (int y = -20; y < 20; y++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				// bind shader, 然后Upload VP矩阵到uniform, 然后调用DrawCall
				Hazel::Renderer::Submit(flatColorShader, m_QuadVertexArray, transform);
			}
		}

		glm::mat4 transform = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
		m_TextureOne->Bind(0);
		Hazel::Renderer::Submit(textureShader, m_QuadVertexArray, transform);

		m_TextureTwo->Bind(0);
		Hazel::Renderer::Submit(textureShader, m_QuadVertexArray, transform);
		// todo: 后续需要把上面代码改为Batch操作
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

