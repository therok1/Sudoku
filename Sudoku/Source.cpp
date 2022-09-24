#include <iostream>
#include <SDL.h>
#include <time.h>

#include "Game.h"
#include "Window.h"

bool init();

int main(int argc, char** args)
{
	srand(time(nullptr));

	Window* WindowObj = new Window();
	Game* GameObj = new Game();

	if (!WindowObj->InitialiseWindow() || !init())
	{
		return 1;
	}

	SDL_SetRenderDrawColor(Window::m_Renderer, 0, 0, 0, 255);

	while (GameObj->GetRunning())
	{
		GameObj->Tick();
		GameObj->EventLoop();
		GameObj->Render();
	}

	delete WindowObj;
	delete GameObj;

	SDL_Quit();

	return 0;
}

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		return false;
	}

	return true;
}