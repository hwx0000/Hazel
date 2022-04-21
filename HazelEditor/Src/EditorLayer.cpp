#include "EditorLayer.h"
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer/Renderer2D.h"
#include "Math/Random.h"
#include <filesystem>

namespace Hazel
{
	EditorLayer::EditorLayer(const std::string& name) :
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

	EditorLayer::~EditorLayer()
	{
		Hazel::Renderer2D::Shutdown();
	}

	void EditorLayer::OnAttach()
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

		m_Framebuffer = Hazel::Framebuffer::Create(1280, 720);

		m_Scene = std::make_shared<Hazel::Scene>();
		Hazel::GameObject& go = m_Scene->CreateGameObjectInScene();

		const Hazel::SpriteRenderer& sr = Hazel::SpriteRenderer({ 0.1f, 0.8f, 0.1f, 1.0f });
		go.AddComponent<Hazel::SpriteRenderer>(sr, glm::vec4{ 0.1f, 0.8f, 0.1f, 1.0f });
	}

	void EditorLayer::OnDettach()
	{
		CORE_LOG("Detach Layer");
	}

	void EditorLayer::OnEvent(Hazel::Event& e)
	{
		m_OrthoCameraController.OnEvent(e);
	}

	void EditorLayer::OnUpdate(const Hazel::Timestep& ts)
	{
		{
			//// 使用的时候, 需要传入一个profileResult对象
			//Hazel::Timer t("CameraController.OnUpdate", [&](const char* name, float duration)
			//{ 
			//	Hazel::ProfileResult profileResult = {name, duration};
			//	m_ProfileResults.push_back(profileResult); 
			//});
			if (m_ViewportFocused && m_ViewportHovered)
				m_OrthoCameraController.OnUpdate(ts);
		}

		// 每帧开始Clear

		// This is for the color for default window 
		// 保留原本默认窗口对应framebuffer的颜色, 注意, 一定要先设置ClearColor, 再去Clear
		Hazel::RenderCommand::SetClearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
		Hazel::RenderCommand::Clear();

		m_Framebuffer->Bind();
		Hazel::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Hazel::RenderCommand::Clear();
		Hazel::Renderer2D::BeginScene(m_OrthoCameraController.GetCamera());
		{
			//Hazel::Renderer2D::DrawQuad({ -0.4f, 0.1f }, { 1.5f, 1.5f }, { 1.0f, 0.0f, 0.0f, 1.0f });
			//Hazel::Renderer2D::DrawQuad({ 0.2f, -0.8f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });
			//Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.2f }, { 0.4f, 0.4f }, m_Texture2D, 2.0f);   		 
			//Hazel::Renderer2D::DrawRotatedQuad({ -0.5f, 0.5f, 0.2f }, { 0.4f, 0.4f }, 45.0f, m_Texture2D, 2.0f);

			const Hazel::GameObject& go = m_Scene->GetGameObjects()[0];
			Hazel::SpriteRenderer sRenderer = m_Scene->GetComponentInGameObject<Hazel::SpriteRenderer>(go);
			//Hazel::Renderer2D::DrawSpriteRenderer(sRenderer, { 0.0f, 0.0f, 0.2f }, { 0.8f, 0.8f });
			Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.2f }, { 0.8f, 0.8f }, {0.1f, 1.0f, 0.1f, 1.0f});

			//static float rotatedAngle = 0.0f;
			//rotatedAngle += ts * 100.0f;

			//float tileSize = 0.18f;
			//float height = 9 * tileSize;
			//float width = 16 * tileSize;

			//for (size_t y = 0; y < 9; y++)
			//	for (size_t x = 0; x < 16; x++)
			//	{
			//		char t = s_MapTiles[x + y * 16];

			//		float xPos = -width / 2.0f + x * tileSize;
			//		float yPos = -(-height / 2.0f + y * tileSize);// y轴坐标取相反数, 是为了跟绘制的地图char数组相同
			//		Hazel::Renderer2D::DrawRotatedQuad({ xPos, yPos, 0.1f }, { tileSize, tileSize }, rotatedAngle, s_Map[t], 1.0f);
			//	}
		}
		Hazel::Renderer2D::EndScene();
		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
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

		ImGui::Begin("Test");
		ImGui::ColorEdit4("Flat Color Picker", glm::value_ptr(m_FlatColor));

		auto& stats = Hazel::Renderer2D::GetStatistics();

		ImGui::Text("DrawCalls: %d", stats.DrawCallCnt);
		ImGui::Text("DrawQuads: %d", stats.DrawQuadCnt);
		ImGui::Text("DrawVertices: %d", stats.DrawVerticesCnt());
		ImGui::Text("DrawTiangles: %d", stats.DrawTrianglesCnt());

		ImGui::End();

		ImGui::Begin("Viewport");
		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Hazel::Application::Get().GetImGuiLayer()->SetViewportFocusedStatus(m_ViewportFocused);
		Hazel::Application::Get().GetImGuiLayer()->SetViewportHoveredStatus(m_ViewportHovered);

		ImVec2 size = ImGui::GetContentRegionAvail();
		glm::vec2 viewportSize = { size.x, size.y };

		// 放前面先画, 是为了防止重新生成Framebuffer的ColorAttachment以后, 当前帧渲染会出现黑屏的情况
		if (viewportSize != m_LastViewportSize)
		{
			m_Framebuffer->ResizeColorAttachment((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
			m_OrthoCameraController.GetCamera().OnResize(viewportSize.x, viewportSize.y);
		}

		ImGui::Image(m_Framebuffer->GetColorAttachmentTexture2DId(), size, { 0,1 }, { 1,0 });

		m_LastViewportSize = viewportSize;

		ImGui::End();

		//m_ProfileResults.clear();
	}
}