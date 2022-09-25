#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <time.h>
#include <memory>

#include "Game.h"
#include "Window.h"

bool init();

int main(int argc, char** args)
{
	srand(time(nullptr));

	std::unique_ptr<Window> WindowObj = std::make_unique<Window>();

	if (!WindowObj->InitialiseWindow() || !init())
	{
		return 1;
	}

	Game* GameObj = new Game(); // Cannot use unique pointers due to destructor being called after TTF library has already been closed which results in an exception

	SDL_SetRenderDrawColor(Window::m_Renderer, 0, 0, 0, 255);

	while (GameObj->GetRunning())
	{
		GameObj->Tick();
		GameObj->EventLoop();
		GameObj->Render();
	}

	delete GameObj;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}

bool init()
{
	bool Fail = false;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Fail = true;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		Fail = true;
	}

	if (TTF_Init() != 0)
	{
		Fail = true;
	}

	return !Fail;
}