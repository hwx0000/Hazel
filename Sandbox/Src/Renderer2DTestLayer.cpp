#include "Renderer2DTestLayer.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer/Renderer2D.h"
#include <filesystem>

Renderer2DTestLayer::Renderer2DTestLayer(const std::string& name) :
m_OrthoCameraController(1.6667f, 1.0f)
{
	Hazel::Renderer2D::Init();

	//std::string texturePath = std::filesystem::current_path().string() + "\\Resources\\HeadIcon.jpg";
	std::string texturePath = std::filesystem::current_path().string() + "\\Resources\\TextureAtlas.png";
	m_Texture2D = Hazel::Texture2D::Create(texturePath);
}

// 16行9列
static const char s_MapTiles[] =
{
// 这种写法其实代表一个长字符串, D代表Dirt土地Tile, W代表Water Tile, S代表路标Tile
// 注意第一个Tile为D, 虽然在数组里坐标为(0,0), 但是在屏幕上对应的坐标应该是(0,1)
"DDWWWWWWWWWWWWWW"
"DDWWWWWWWWWWWWWW"
"DDDDDDDDDDDWWWWW"
"DDDDDSDDDDDWWWWW"
"DDDDDDDDDDDWWWWW"
"DDWWWWWWWWWWWWWW"
"DDWWWWWWWWWDDSDD"
"DDWWWWWWWWWWWWWW"
"DDWWWWWWWWWWWWWW"
};

static std::unordered_map<char, std::shared_ptr<Hazel::SubTexture2D>> s_Map;

Renderer2DTestLayer::~Renderer2DTestLayer()
{
	Hazel::Renderer2D::Shutdown();
}

void Renderer2DTestLayer::OnAttach()
{
	CORE_LOG("Init Layer");


	Hazel::SubTexture2D subT1(m_Texture2D, { 0.7f, 5.0f / 9.0f }, { 0.75f, 6.0f / 9.0f });
	std::shared_ptr<Hazel::SubTexture2D> waterTileTex = std::make_shared<Hazel::SubTexture2D>(subT1);
	s_Map['W'] = waterTileTex;

	Hazel::SubTexture2D subT2(m_Texture2D, { 0.1f, 2.0f / 9.0f }, { 0.15f, 3.0f / 9.0f });
	std::shared_ptr<Hazel::SubTexture2D> dirtTileTex = std::make_shared<Hazel::SubTexture2D>(subT2);
	s_Map['D'] = dirtTileTex;

	Hazel::SubTexture2D subT3(m_Texture2D, { 0.3f, 4.0f / 9.0f }, { 0.35f, 5.0f / 9.0f });
	std::shared_ptr<Hazel::SubTexture2D> roadSignTex = std::make_shared<Hazel::SubTexture2D>(subT3);
	s_Map['S'] = roadSignTex;
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
	{
		//// 使用的时候, 需要传入一个profileResult对象
		//Hazel::Timer t("CameraController.OnUpdate", [&](const char* name, float duration)
		//{ 
		//	Hazel::ProfileResult profileResult = {name, duration};
		//	m_ProfileResults.push_back(profileResult); 
		//});
		m_OrthoCameraController.OnUpdate(ts);
	}

	// 每帧开始Clear
	Hazel::RenderCommand::Clear();
	Hazel::RenderCommand::ClearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	Hazel::Renderer2D::BeginScene(m_OrthoCameraController.GetCamera());
	{
		//Hazel::Renderer2D::DrawQuad({ -0.4f, 0.1f }, { 1.5f, 1.5f }, { 1.0f, 0.0f, 0.0f, 1.0f });
		//Hazel::Renderer2D::DrawQuad({ 0.2f, -0.8f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });
		//Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.2f }, { 0.4f, 0.4f }, m_Texture2D, 2.0f);   		 
		//Hazel::Renderer2D::DrawRotatedQuad({ -0.5f, 0.5f, 0.2f }, { 0.4f, 0.4f }, 45.0f, m_Texture2D, 2.0f);


		float tileSize = 0.18f;
		float height = 9 * tileSize;
		float width = 16 * tileSize;

		for (size_t y = 0; y < 9; y++)
			for (size_t x = 0; x < 16; x++)
			{
				char t = s_MapTiles[x + y * 16];

				float xPos = -width / 2.0f + x * tileSize;
				float yPos = -(-height / 2.0f + y * tileSize);// y轴坐标取相反数, 是为了跟绘制的地图char数组相同
				Hazel::Renderer2D::DrawQuad({ xPos, yPos, 0.1f }, { tileSize, tileSize }, s_Map[t], 1.0f);
			}
	}
	Hazel::Renderer2D::EndScene();
}

void Renderer2DTestLayer::OnImGuiRender()
{
	ImGui::Begin("Test");
	ImGui::ColorEdit4("Flat Color Picker", glm::value_ptr(m_FlatColor));

	//for (size_t i = 0; i < m_ProfileResults.size(); i++)
	//{
	//	auto& result = m_ProfileResults[i];
	//	char label[50];
	//	strcpy_s(label, result.Name);
	//	strcat_s(label, ": %.3fms ");		// 保留三位小数
	//	ImGui::Text(label, result.Time);// 打印Profile条目的名字和time
	//}

	auto& stats = Hazel::Renderer2D::GetStatistics();

	ImGui::Text("DrawCalls: %d", stats.DrawCallCnt);
	ImGui::Text("DrawQuads: %d", stats.DrawQuadCnt);
	ImGui::Text("DrawVertices: %d", stats.DrawVerticesCnt());
	ImGui::Text("DrawTiangles: %d", stats.DrawTrianglesCnt());


	m_ProfileResults.clear();
	ImGui::End();
}