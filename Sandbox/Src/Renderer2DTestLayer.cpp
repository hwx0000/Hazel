#include "Renderer2DTestLayer.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer/RenderCommandRegister.h"
#include "Math/Random.h"
#include <filesystem>

Renderer2DTestLayer::Renderer2DTestLayer(const std::string& name) :
m_OrthoCameraController(1.6667f, 1.0f)
{
	Hazel::RenderCommandRegister::Init();

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
	Hazel::RenderCommandRegister::Shutdown();
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

	Hazel::FramebufferSpecification spec;
	m_Framebuffer = Hazel::Framebuffer::Create(spec);
}

void Renderer2DTestLayer::OnDetach()
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
	Hazel::RenderCommand::SetClearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

	Hazel::RenderCommandRegister::BeginScene(m_OrthoCameraController.GetCamera());
	{
		m_Framebuffer->Bind();
		//Hazel::Renderer2D::DrawQuad({ -0.4f, 0.1f }, { 1.5f, 1.5f }, { 1.0f, 0.0f, 0.0f, 1.0f });
		//Hazel::Renderer2D::DrawQuad({ 0.2f, -0.8f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });
		//Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.2f }, { 0.4f, 0.4f }, m_Texture2D, 2.0f);   		 
		//Hazel::Renderer2D::DrawRotatedQuad({ -0.5f, 0.5f, 0.2f }, { 0.4f, 0.4f }, 45.0f, m_Texture2D, 2.0f);

		static float rotatedAngle = 0.0f;
		rotatedAngle += ts * 100.0f;

		float tileSize = 0.18f;
		float height = 9 * tileSize;
		float width = 16 * tileSize;

		for (size_t y = 0; y < 9; y++)
			for (size_t x = 0; x < 16; x++)
			{
				char t = s_MapTiles[x + y * 16];

				float xPos = -width / 2.0f + x * tileSize;
				float yPos = -(-height / 2.0f + y * tileSize);// y轴坐标取相反数, 是为了跟绘制的地图char数组相同
				//Hazel::RenderCommandRegister::DrawRotatedQuad2D({ xPos, yPos, 0.1f }, { tileSize, tileSize }, rotatedAngle, s_Map[t], 1.0f);
			}
	}
	Hazel::RenderCommandRegister::EndScene();

	m_Framebuffer->Unbind();
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

	auto& stats = Hazel::RenderCommandRegister::GetStatistics();

	ImGui::Text("DrawCalls: %d", stats.DrawCallCnt);
	ImGui::Text("DrawQuads: %d", stats.DrawQuadCnt);
	ImGui::Text("DrawVertices: %d", stats.DrawVerticesCnt());
	ImGui::Text("DrawTiangles: %d", stats.DrawTrianglesCnt());

	ImGui::Image(m_Framebuffer->GetColorAttachmentTexture2DId(), { 1080, 720 });
	//ImGui::Image(m_Texture2D->GetTextureId(), { 1080, 720 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });


	m_ProfileResults.clear();
	ImGui::End();

	// 下面是绘制Dockspace的代码
	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->GetWorkPos());
		ImGui::SetNextWindowSize(viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	static bool s = true;
	static bool* s_bool = &s;
	ImGui::Begin("DockSpace Demo", s_bool, window_flags);
	//ImGui::Begin("DockSpace Demo", p_open, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	else
	{
		//ShowDockingDisabledMessage();
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Options"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
			ImGui::MenuItem("Padding", NULL, &opt_padding);
			ImGui::Separator();

			if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
			if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
			if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
			if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
			if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
			ImGui::Separator();

			if (ImGui::MenuItem("Close", NULL, false, s_bool != NULL))
				*s_bool = false;
			ImGui::EndMenu();
		}
		/*HelpMarker(
			"When docking is enabled, you can ALWAYS dock MOST window into another! Try it now!" "\n\n"
			" > if io.ConfigDockingWithShift==false (default):" "\n"
			"   drag windows from title bar to dock" "\n"
			" > if io.ConfigDockingWithShift==true:" "\n"
			"   drag windows from anywhere and hold Shift to dock" "\n\n"
			"This demo app has nothing to do with it!" "\n\n"
			"This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window. This is useful so you can decorate your main application window (e.g. with a menu bar)." "\n\n"
			"ImGui::DockSpace() comes with one hard constraint: it needs to be submitted _before_ any window which may be docked into it. Therefore, if you use a dock spot as the central point of your application, you'll probably want it to be part of the very first window you are submitting to imgui every frame." "\n\n"
			"(NB: because of this constraint, the implicit \"Debug\" window can not be docked into an explicit DockSpace() node, because that window is submitted as part of the NewFrame() call. An easy workaround is that you can create your own implicit \"Debug##2\" window after calling DockSpace() and leave it in the window stack for anyone to use.)"
		);*/

		ImGui::EndMenuBar();
	}

	ImGui::End();
}