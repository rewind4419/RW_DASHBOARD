#include <stdio.h>
#define SDL_MAIN_HANDLED
#include "loop.h"
#include "window.h"


int main()
{
	Window* window = new Window;
	window->Loop->running = true;
	while (window->Loop->running)
	{
		window->Update();
	}
	window->~Window();
}