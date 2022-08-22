#include "EditorLayer.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer/Renderer2D.h"
#include "Math/Random.h"
#include <filesystem>
#include "ECS/Components/Transform.h"
#include "ECS/SceneSerializer.h"
#include "Utils/PlatformUtils.h"
#include "ImGuizmo.h"

namespace Hazel
{
	bool hasEnding(std::string const& fullString, std::string const& ending) 
	{
		if (fullString.length() >= ending.length()) 
		{
			return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
		}
		else 
			return false;
	}

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

		m_ViewportFramebuffer = Hazel::Framebuffer::Create(1280, 720);

		m_Scene = std::make_shared<Hazel::Scene>();

		//// 1. 创建MySquare对象
		//Hazel::GameObject& go = m_Scene->CreateGameObjectInScene(m_Scene, "MySquare");
		//go.AddComponent<Hazel::SpriteRenderer>(glm::vec4{ 0.1f, 0.8f, 0.1f, 1.0f });

		//// 2. 创建MainCamera对象
		//Hazel::GameObject& cameraGo = m_Scene->CreateGameObjectInScene(m_Scene, "MainCamera");
		//// 添加CameraComponent
		//CameraComponent& camera = cameraGo.AddComponent<Hazel::CameraComponent>();
		//camera.SetRenderTargetSize(300, 300);

		// TODO: 暂时默认绑定到第一个CameraComponent上, 实际应该是点谁, 就绑定到谁
		m_CameraComponentFramebuffer = Hazel::Framebuffer::Create(350, 350);

		//// 3. 创建MySquare2对象
		//Hazel::GameObject& go2 = m_Scene->CreateGameObjectInScene(m_Scene, "MySquare2");
		//go2.AddComponent<Hazel::SpriteRenderer>(glm::vec4{ 0.8f, 0.1f, 0.1f, 1.0f });
		//go2.SetPosition({ 1,0,0 });

		SceneSerializer::Deserialize(m_Scene, "DefaultScene.scene");

		m_SceneHierarchyPanel.SetContext(m_Scene);
	}

	void EditorLayer::OnDetach()
	{
		CORE_LOG("Detach Layer");
	}

	void EditorLayer::OnEvent(Hazel::Event& e)
	{
		if (e.GetEventType() == Hazel::EventType::KeyPressed)
		{
			KeyPressedEvent* kpe = dynamic_cast<Hazel::KeyPressedEvent*>(&e);
			if (kpe->GetKeycode() == HZ_KEY_Q)
			{
				m_Option = ToolbarOptions::Default;
				kpe->MarkHandled();
			}
			if (kpe->GetKeycode() == HZ_KEY_W)
			{
				m_Option = ToolbarOptions::Translate;
				kpe->MarkHandled();
			}
			if (kpe->GetKeycode() == HZ_KEY_E)
			{
				m_Option = ToolbarOptions::Rotation;
				kpe->MarkHandled();
			}
			if (kpe->GetKeycode() == HZ_KEY_R)
			{
				m_Option = ToolbarOptions::Scale;
				kpe->MarkHandled();
			}
		}
		
		m_OrthoCameraController.OnEvent(e);
	}

	void EditorLayer::OnUpdate(const Hazel::Timestep& ts)
	{
		if (m_ViewportFocused && m_ViewportHovered)
			m_OrthoCameraController.OnUpdate(ts);

		// 每帧开始Clear

		// This is for the color for default window 
		// 保留原本默认窗口对应framebuffer的颜色, 注意, 一定要先设置ClearColor, 再去Clear
		Hazel::RenderCommand::SetClearColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
		Hazel::RenderCommand::Clear();

		// 先渲染Viewport
		m_ViewportFramebuffer->Bind();
		Hazel::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Hazel::RenderCommand::Clear();

		Hazel::Renderer2D::BeginScene(m_OrthoCameraController.GetCamera());
		Render();
		Hazel::Renderer2D::EndScene();
		m_ViewportFramebuffer->Unbind();

		// 再渲染各个CameraComponent
		if (m_ShowCameraComponent)
		{
			m_CameraComponentFramebuffer->Bind();
			Hazel::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
			Hazel::RenderCommand::Clear();

			auto gos = m_Scene->GetGameObjectsByComponent<CameraComponent>();

			if (gos.size() > 0)
			{
				const Hazel::GameObject& go = gos[0];
				Hazel::CameraComponent& cam = m_Scene->GetComponentInGameObject<Hazel::CameraComponent>(go);

				Hazel::Renderer2D::BeginScene(cam, go.GetTransformMat());
				Render();
				Hazel::Renderer2D::EndScene();
			}

			m_CameraComponentFramebuffer->Unbind();
		}
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

		// 绘制toolbar
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save Scene")) 
				{
					// 返回的是绝对路径
					std::optional<std::string> filePath = FileDialogWindowUtils::SaveFile("Hazel Scene (*.scene)\0*.scene\0");

					if (filePath.has_value())
					{
						std::string path = filePath.value();

						if (!hasEnding(path, ".scene"))
							path = path + ".scene";

						if (m_Scene)
							SceneSerializer::Serialize(m_Scene, path.c_str());
					}
				}

				if (ImGui::MenuItem("Load Scene"))
				{
					if (m_Scene)
					{
						std::optional<std::string> filePath = FileDialogWindowUtils::OpenFile("Hazel Scene (*.scene)\0*.scene\0");
						if (filePath.has_value())
						{
							// 前面的Hazel Scene(*.scene)是展示在filter里的text, 后面的*.scene代表显示的文件后缀类型
							if (m_Scene)
								SceneSerializer::Deserialize(m_Scene, filePath.value().c_str());
						}
					}
				}

				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		ImGui::End();

		ImGui::Begin("Render Stats");
		auto& stats = Hazel::Renderer2D::GetStatistics();

		ImGui::Text("DrawCalls: %d", stats.DrawCallCnt);
		ImGui::Text("DrawQuads: %d", stats.DrawQuadCnt);
		ImGui::Text("DrawVertices: %d", stats.DrawVerticesCnt());
		ImGui::Text("DrawTiangles: %d", stats.DrawTrianglesCnt());

		ImGui::Checkbox("Show Camera Component Window", &m_ShowCameraComponent);

		ImGui::End();

		// 绘制CameraComponent对应的Window, 感觉放到HazelEditor里比Hazel里更好一点
		if (m_ShowCameraComponent)
		{
			auto wholeWndStartPos = ImGui::GetMainViewport()->Pos;
			auto size = ImGui::GetMainViewport()->Size;

			ImVec2 subWndSize(300, 300);
			ImVec2 subWndStartPos;
			subWndStartPos.x = wholeWndStartPos.x + size.x - subWndSize.x;
			subWndStartPos.y = wholeWndStartPos.y + size.y - subWndSize.y;

			// TODO: optimization, 可以只在resize时才设置窗口大小
			ImGui::SetNextWindowPos(subWndStartPos, ImGuiCond_Always);
			ImGui::SetNextWindowSize(subWndSize);

			ImGui::Begin("Camera View", &m_ShowCameraComponent, ImGuiWindowFlags_NoMove);
			// 好像是出现的ImGui窗口存在Border, 所以要设置280的size
			ImGui::Image(m_CameraComponentFramebuffer->GetColorAttachmentTexture2DId(), {280, 280}, { 0,1 }, { 1,0 });
			ImGui::End();
		}


		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Hazel::Application::Get().GetImGuiLayer()->SetViewportFocusedStatus(m_ViewportFocused);
		Hazel::Application::Get().GetImGuiLayer()->SetViewportHoveredStatus(m_ViewportHovered);

		ImVec2 size = ImGui::GetContentRegionAvail();
		glm::vec2 viewportSize = { size.x, size.y };

		// 当Viewport的Size改变时, 更新Framebuffer的ColorAttachment的Size, 同时调用其他函数
		// 放前面先画, 是为了防止重新生成Framebuffer的ColorAttachment以后, 当前帧渲染会出现黑屏的情况
		if (viewportSize != m_LastViewportSize)
		{
			// 先Resize Framebuffer
			m_ViewportFramebuffer->ResizeColorAttachment((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
			m_OrthoCameraController.GetCamera().OnResize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
			m_Scene->OnViewportResized(viewportSize.x, viewportSize.y);
		}

		ImGui::Image(m_ViewportFramebuffer->GetColorAttachmentTexture2DId(), size, { 0,1 }, { 1,0 });

		m_LastViewportSize = viewportSize;

		uint32_t id = m_SceneHierarchyPanel.GetSelectedGameObjectId();
		bool succ;
		GameObject& selected = m_Scene->GetGameObjectById(id, succ);
		if (succ)
		{
			bool bOrthographic = m_OrthoCameraController.GetCamera().IsOrthographicCamera();
			ImGuizmo::SetOrthographic(bOrthographic);
			ImGuizmo::BeginFrame();

			glm::mat4 v = m_OrthoCameraController.GetCamera().GetViewMatrix();
			glm::mat4 p = m_OrthoCameraController.GetCamera().GetProjectionMatrix();
			glm::mat4 trans = selected.GetTransformMat();
			EditTransform((float*)(&v), (float*)(&p), (float*)(&trans), true);
			selected.SetTransformMat(trans);
		}
		ImGui::End();

		//m_ProfileResults.clear();

		m_SceneHierarchyPanel.OnImGuiRender();
	}


	// 此函数会为每个fbo都调用一次, 比如为Viewport和每个CameraComponent都调用一次
	void EditorLayer::Render()
	{
		std::vector<GameObject> gos = m_Scene->GetGameObjectsByComponent<Hazel::SpriteRenderer>();

		for (size_t i = 0; i < gos.size(); i++)
		{
			Hazel::GameObject& go = gos[i];
			Hazel::SpriteRenderer& sRenderer = go.GetComponent<Hazel::SpriteRenderer>();
			Hazel::Transform& t = go.GetComponent<Hazel::Transform>();
			Hazel::Renderer2D::DrawSpriteRenderer(sRenderer, t.Translation, t.Rotation.z, { t.Scale.x, t.Scale.y });
		}
	}

	static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
	
	// 绘制Viewport对应的窗口, 从而绘制gizmos, 传入的是camera的V和P矩阵, matrix的Transform对应的矩阵
	void EditorLayer::EditTransform(float* cameraView, float* cameraProjection, float* matrix, bool editTransformDecomposition)
	{
		switch (m_Option)
		{
		case ToolbarOptions::Default:
			break;
		case ToolbarOptions::Translate:
			mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
			break;
		case ToolbarOptions::Rotation:
			mCurrentGizmoOperation = ImGuizmo::ROTATE;
			break;
		case ToolbarOptions::Scale:
			mCurrentGizmoOperation = ImGuizmo::SCALE;
			break;
		default:
			break;
		}

		static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
		static bool useSnap = false;
		static float snap[3] = { 1.f, 1.f, 1.f };
		static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
		static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
		static bool boundSizing = false;
		static bool boundSizingSnap = false;

		ImGuiIO& io = ImGui::GetIO();
		float viewManipulateRight = io.DisplaySize.x;
		float viewManipulateTop = 0;
		static ImGuiWindowFlags gizmoWindowFlags = 0;

		ImGui::SetNextWindowSize(ImVec2(800, 400), ImGuiCond_Appearing);
		ImGui::SetNextWindowPos(ImVec2(400, 20), ImGuiCond_Appearing);

		ImGuizmo::SetDrawlist();

		// ImGuizmo的绘制范围应该与Viewport窗口相同, 绘制(相对于显示器的)地点也应该相同
		float windowWidth = (float)ImGui::GetWindowWidth();
		float windowHeight = (float)ImGui::GetWindowHeight();
		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
		
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		gizmoWindowFlags = ImGui::IsWindowHovered() && ImGui::IsMouseHoveringRect
			(window->InnerRect.Min, window->InnerRect.Max) ? ImGuiWindowFlags_NoMove : 0;


		//ImGuizmo::DrawGrid(cameraView, cameraProjection, identityMatrix, 100.f);
		//ImGuizmo::DrawCubes(cameraView, cameraProjection, &objectMatrix[0][0], gizmoCount);
		ImGuizmo::Manipulate(cameraView, cameraProjection, mCurrentGizmoOperation, mCurrentGizmoMode, matrix, NULL, 
			useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);

		//viewManipulateRight = ImGui::GetWindowPos().x + windowWidth;
		//viewManipulateTop = ImGui::GetWindowPos().y;
		//float camDistance = 8.f;
		//ImGuizmo::ViewManipulate(cameraView, camDistance, ImVec2(viewManipulateRight - 128, viewManipulateTop), ImVec2(128, 128), 0x10101010);
	}

}	