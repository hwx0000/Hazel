#include "hzpch.h"
#include "ImGuiLayer.h"
#include "imgui.h"
#include <stdio.h>
#include "Core/Application.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

// Temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

Hazel::ImGuiLayer::ImGuiLayer()
{
}

Hazel::ImGuiLayer::~ImGuiLayer()
{
}

// ImGuiLayer的Init函数
void Hazel::ImGuiLayer::OnAttach()
{
	// 这里的函数，参考了ImGui上的docking分支给的例子：example_glfw_opengl3的文件里的main函数
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	// 1. 创建ImGui Contex
	ImGui::CreateContext();

	// 2. IO相关的Flag设置, 目前允许键盘输入、允许Dokcing、允许多个Viewport
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;
	// 加载fonts
	io.FontDefault = io.Fonts->AddFontFromFileTTF("Resources/Fonts/SourceSansPro-Regular.ttf", 18);
	io.Fonts->AddFontFromFileTTF("Resources/Fonts/SourceSansPro-Bold.ttf", 18);

	// 3. 设置主题颜色
	ImGui::StyleColorsDark();
	SetDarkThemeColors();
	//ImGui::StyleColorsClassic();

	// 4. 设置窗口Style和背景颜色的透明度
	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;// WindowRounding代表窗口角落的值, 设置为0.0代表是矩形窗口
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;// 窗口背景透明度
	}

	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	
	// 5. glfw相关的初始化
	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);

	// 6. OpenGL相关的初始化
	ImGui_ImplOpenGL3_Init("#version 410");
}

void Hazel::ImGuiLayer::OnDetach()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Hazel::ImGuiLayer::OnImGuiRender()
{
	//static bool show = true;
	//ImGui::ShowDemoWindow(&show);
}

void Hazel::ImGuiLayer::OnEvent(Event &e)
{
	// 只有鼠标在Viewport窗口上、且窗口被Focus时, Viewport窗口才可以接收到Event
	if (!(m_ViewportFocused/* && m_ViewportHovered*/))// Viewport区域以外的Event会被ImGui接受
		e.MarkHandled();
}

// Begin和End之间指向OnImGuiRender里的函数
void Hazel::ImGuiLayer::Begin()
{
	// 下面这一部分原本属于Update函数里，现在这部分抽出来作为了接口，可以在exe选择性的进行Render
	// Start the Dear ImGui frame

	// 这个函数应该只会执行一次具体的内容, 会在里面创建OpenGL的ShaderProgram
	ImGui_ImplOpenGL3_NewFrame();

	// 从glfw库里获取 时间、鼠标位置、窗口和Viewport大小等参数, 赋值给ImGui::IO
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();
}

void Hazel::ImGuiLayer::End()
{        
	ImGuiIO& io = ImGui::GetIO();
	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

void Hazel::ImGuiLayer::SetDarkThemeColors()
{
	auto& colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

	// Headers
	colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Buttons
	colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Frame BG
	colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Tabs
	colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
	colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
	colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

	// Title
	colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
}
