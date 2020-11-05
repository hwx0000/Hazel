#include "hzpch.h"
#include "ImGuiLayer.h"
#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include <stdio.h>
#include "Hazel/Application.h"

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
	// ����ĺ������ο���ImGui�������ӣ�example_glfw_opengl3���ļ����main����
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	
	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)

	// ָ��ImGui��IO����
	// TEMPORARY: ֻ����ʱ��ôд��������Ҫʹ��Hazel�Լ���װ��KeyCode��
	io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
	io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
	io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
	io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
	io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
	io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
	io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
	io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
	io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
	io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
	io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
	io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
	io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

	// ImGuiΪopengl���ĳ�ʼ����
	ImGui_ImplOpenGL3_Init("#version 410");
}

void Hazel::ImGuiLayer::OnDettach()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}

void Hazel::ImGuiLayer::OnEvent(Event &e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&ImGuiLayer::OnMouseButtonPressed, this, std::placeholders::_1));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&ImGuiLayer::OnMouseButtonReleased, this, std::placeholders::_1));
	dispatcher.Dispatch<MouseMovedEvent>(std::bind(&ImGuiLayer::OnMouseCursorMoved, this, std::placeholders::_1));
	dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&ImGuiLayer::OnMouseScrolled, this, std::placeholders::_1));
	dispatcher.Dispatch<KeyPressedEvent>(std::bind(&ImGuiLayer::OnKeyPressed, this, std::placeholders::_1));
	dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&ImGuiLayer::OnKeyReleased, this, std::placeholders::_1));
	dispatcher.Dispatch<KeyTypedEvent>(std::bind(&ImGuiLayer::OnKeyTyped, this, std::placeholders::_1));
}

void Hazel::ImGuiLayer::OnUpdate()
{
	// ����Ҳ�ǲ���ImGui����ExampleдUpdate�ĺ�������Ҫ�������¹���
	// ����FrameȻ�����Render
	// ���ݴ��ڴ�С����̬��ImGui���ô���չʾ��С
	// ����DeltaTime


	ImGuiIO& io = ImGui::GetIO();
	//LOG(io.Fonts->IsBuilt() && "Font atlas not built! It is generally built by the renderer backend. Missing call to renderer _NewFrame() function? e.g. ImGui_ImplOpenGL3_NewFrame().");

	// Setup display size (every frame to accommodate for window resizing)
	io.DisplaySize = ImVec2((float)Application::Get().GetWindow().GetWindowWidth()
		, (float)Application::Get().GetWindow().GetWindowHeight());

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	
	// Setup time step
	double current_time = glfwGetTime();
	io.DeltaTime = m_Time > 0.0 ? (float)(current_time - m_Time) : (float)(1.0f / 60.0f);
	m_Time = current_time;

	// todo�� ����������ÿ��Loop��Callback
	// ����������Movement

	ImGui::NewFrame();
	static bool showWindow = true;
	ImGui::ShowDemoWindow(&showWindow);
	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool Hazel::ImGuiLayer::OnMouseCursorMoved(MouseMovedEvent &e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)e.GetXPos(), (float)e.GetYPos());
	return false;
}

bool Hazel::ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[e.GetMouseButton()] = true;
	return false;
}

bool Hazel::ImGuiLayer::OnMouseButtonReleased(MouseButtonReleasedEvent &e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[e.GetMouseButton()] = false;
	return false;
}

bool Hazel::ImGuiLayer::OnMouseScrolled(MouseScrolledEvent &e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheelH += (float)e.GetXOffset();
	io.MouseWheel += (float)e.GetYOffset();
	return false;
}

bool Hazel::ImGuiLayer::OnKeyPressed(KeyPressedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[e.GetKeycode()] = true;

	// ���¼����Թ������Զ��⴦��
	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

	return false;
}

bool Hazel::ImGuiLayer::OnKeyReleased(KeyReleasedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[e.GetKeycode()] = false;

	// ���¼����Թ������Զ��⴦��
	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

	return false;
}

bool Hazel::ImGuiLayer::OnKeyTyped(KeyTypedEvent &e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.AddInputCharacter(e.GetKeycode());
	return false;
}

bool Hazel::ImGuiLayer::OnWindowResized(WindowResizedEvent &e)
{
	// ÿ��Window���ڴ�С�ı��ʱ��Ҳ����ô˺�����ImGui��Demoʵ����û�в������ַ���
	// ������ÿ֡ȥGet���ڵĴ�С��Ȼ���������ã���������ע����ʾ
	// Setup display size (every frame to accommodate for window resizing)
	/*int w, h;
	int display_w, display_h;
	glfwGetWindowSize(g_Window, &w, &h);
	glfwGetFramebufferSize(g_Window, &display_w, &display_h);
	io.DisplaySize = ImVec2((float)w, (float)h);
	if (w > 0 && h > 0)
		io.DisplayFramebufferScale = ImVec2((float)display_w / w, (float)display_h / h);*/

	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(e.GetWindowWidth(), e.GetWindowHeight());
	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
	glViewport(0, 0, e.GetWindowWidth(), e.GetWindowHeight());

	return false;
}
