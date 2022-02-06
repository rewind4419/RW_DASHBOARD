#include "window.h"
#include "glad\glad.h"
#include "SDL\SDL.h"
#include <iostream>
#include "imgui\imgui.h"
#include "imgui\imgui_impl_opengl3.h"
#include "imgui\imgui_impl_sdl.h"
#include <thread>
#include "loop.h"
#include "net\net.h"
#include "cam\createcam.h"

Window::Window()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	m_window = SDL_CreateWindow("RW_DASH", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280 / 1.15, 720 / 1.25, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	if (m_renderer == nullptr) {
		std::cerr << "SDL2 Renderer couldn't be created. Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	m_gl_context = SDL_GL_CreateContext(m_window);

	// Load GL extensions using glad
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cerr << "Failed to initialize the OpenGL context." << std::endl;
		exit(1);
	}

	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	// Imgui init

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& m_io = ImGui::GetIO(); (void)m_io;

	m_io.DisplaySize = ImVec2(dm.w, dm.h);
	m_io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 16.0f, NULL, NULL);
	m_io.ConfigWindowsMoveFromTitleBarOnly = true;
	m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	m_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	m_io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;


	Window::StyleColorsLightGreen(&ImGui::GetStyle());

	ImGui_ImplSDL2_InitForOpenGL(m_window, m_gl_context);
	ImGui_ImplOpenGL3_Init();

	windowopen = true;

}

void Window::Update()
{

	//time to make this not like protil plz
	//start init
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			std::string s(SDL_GetWindowTitle(m_window));
			SDL_SetWindowTitle(m_window, (s + " (Closing)").c_str());
			Loop->running = false;
		}
		ImGui_ImplSDL2_ProcessEvent(&event);
	}

	glClearColor(ImGui::GetStyle().Colors[ImGuiCol_WindowBg].x, ImGui::GetStyle().Colors[ImGuiCol_WindowBg].y, ImGui::GetStyle().Colors[ImGuiCol_WindowBg].z, ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport((ImGuiViewport*)0, ImGuiDockNodeFlags_AutoHideTabBar);

	int w;
	int h;
	SDL_GetWindowSize(m_window, &w, &h);
	//end init

	//put your crap here

	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File"))
	{
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("View"))
	{
		ImGui::MenuItem("Camera", (const char*) 0, &createcamwind);
		if (ImGui::BeginMenu("Values"))
		{
			ImGui::MenuItem("Encoder", (const char*)0, nullptr);
			ImGui::MenuItem("Color Sensor", (const char*)0, nullptr);
			ImGui::MenuItem("Battery Percentage", (const char*)0, nullptr);
			ImGui::MenuItem("Current Draw", (const char*)0, nullptr);
			ImGui::MenuItem("Voltage Draw", (const char*)0, nullptr);
			ImGui::EndMenu();
		}

		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();

	if (createcamwind)
		showcreatecam();

	//start deinit
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	SDL_GL_MakeCurrent(m_window, m_gl_context);

	SDL_GL_SwapWindow(m_window);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	//enddeinit
}

Window::~Window()
{
	SDL_GL_DeleteContext(m_gl_context);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	SDL_Quit();
}


void Window::StyleColorsLightGreen(ImGuiStyle* dst)
{
	ImGuiStyle* style = dst ? dst : &ImGui::GetStyle();
	ImVec4* colors = style->Colors;

	style->WindowRounding = 2.0f;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows
	style->ScrollbarRounding = 3.0f;             // Radius of grab corners rounding for scrollbar
	style->GrabRounding = 2.0f;             // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
	style->AntiAliasedLines = true;
	style->AntiAliasedFill = true;
	style->WindowRounding = 2;
	style->ChildRounding = 2;
	style->ScrollbarSize = 16;
	style->ScrollbarRounding = 3;
	style->GrabRounding = 2;
	style->ItemSpacing.x = 10;
	style->ItemSpacing.y = 4;
	style->IndentSpacing = 22;
	style->FramePadding.x = 6;
	style->FramePadding.y = 4;
	style->Alpha = 1.0f;
	style->FrameRounding = 3.0f;

	colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	//colors[ImGuiCol_ChildWindowBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.93f, 0.93f, 0.93f, 0.98f);
	colors[ImGuiCol_Border] = ImVec4(0.71f, 0.71f, 0.71f, 0.08f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.04f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.71f, 0.71f, 0.71f, 0.55f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.94f, 0.94f, 0.94f, 0.55f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.71f, 0.78f, 0.69f, 0.98f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.82f, 0.78f, 0.78f, 0.51f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.61f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.90f, 0.90f, 0.90f, 0.30f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.92f, 0.92f, 0.78f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.184f, 0.407f, 0.193f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.71f, 0.78f, 0.69f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.725f, 0.805f, 0.702f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.793f, 0.900f, 0.836f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.71f, 0.78f, 0.69f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.71f, 0.78f, 0.69f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.71f, 0.78f, 0.69f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.45f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_NavHighlight] = colors[ImGuiCol_HeaderHovered];
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
}
