#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <time.h>

#include "Game.h"
#include "Manager.h"

bool init();

int main(int argc, char** args)
{
	srand(time(nullptr));

	if (!Manager::InitialiseWindow(1280, 720, "Sudoku") || !init())
	{
		return 1;
	}

	std::unique_ptr<Game> GameObj = std::make_unique<Game>();

	while (GameObj->GetRunning())
	{
		GameObj->Tick();
		GameObj->EventLoop();
		GameObj->Render();
	}

	GameObj.reset();

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}

bool init()
{
	return !(SDL_Init(SDL_INIT_EVERYTHING) != 0 || IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG || TTF_Init() != 0);
}