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

void Hazel::ImGuiLayer::OnAttach()
{
	// 这里的函数，参考了ImGui上的docking分支给的例子：example_glfw_opengl3的文件里的main函数
 // Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");
}

void Hazel::ImGuiLayer::OnDettach()
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
	if (!(m_ViewportFocused && m_ViewportHovered))// Viewport区域以外的Event会被ImGui接受
		e.MarkHandled();
}

void Hazel::ImGuiLayer::Begin()
{
	// 下面这一部分原本属于Update函数里，现在这部分抽出来作为了接口，可以在exe选择性的进行Render
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
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
