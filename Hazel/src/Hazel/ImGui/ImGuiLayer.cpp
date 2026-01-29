#include "hzpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


#include "Hazel/Application.h"

// Temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // 启用键盘导航
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // 启用游戏手柄导航
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // 启用停靠功
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // 启用多视口功能
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;//如果启用，多视口窗口不会在任务栏显示图标
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;      //如果启用，多视口窗口不会合并

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();						//获取ImGui的样式对象
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)		
		{
			style.WindowRounding = 0.0f;							//将窗口的圆角设置为0
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
		
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::OnImGuiRender()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		//Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

}
