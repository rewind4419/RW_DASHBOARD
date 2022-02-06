#pragma once

typedef struct SDL_Window SDL_Window;
struct SDL_Renderer;
typedef void* SDL_GLContext;
struct ImGuiIO;

#include "loop.h"
#include "imgui\imgui.h"

class Window
{
	public: 
		Window();
		void Update();
		~Window();
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		SDL_GLContext m_gl_context;
		bool windowopen = false;
		void StyleColorsLightGreen(ImGuiStyle* dst);
		loop* Loop = new loop;
private :
	//prepare to lose braincells
	bool createcamwind = false;
};