#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <time.h>
#include <memory>
#include <chrono>
#include <sstream>

#include "Game.h"
#include "Manager.h"

using namespace std::literals;

bool init();

int main(int argc, char** args)
{
	srand(time(nullptr));

	if (!Manager::InitialiseWindow(1280, 720, "Sudoku") || !init())
	{
		return 1;
	}

	Game* GameObj = new Game();

	const auto Time = 1s;
	const auto TargetTime = 1s / 60;
	auto CurrentTime = std::chrono::steady_clock::now();
	auto Accumulator = 0ns;
	
	while (GameObj->GetRunning())
	{
		auto NewTime = std::chrono::steady_clock::now();
		auto FrameTime = NewTime - CurrentTime;
		CurrentTime = NewTime;

		Accumulator += FrameTime;

		if (Accumulator >= TargetTime)
		{
			GameObj->Tick();
			GameObj->EventLoop();
			GameObj->Render();

			Accumulator -= std::chrono::duration_cast<std::chrono::nanoseconds>(TargetTime);
		}

		if (FrameTime != 0ns)
		{
			std::ostringstream Stream;
			Stream << (1s / FrameTime);
			Window.FPS = std::stof(Stream.str());

			SDL_SetWindowTitle(Window.Window, (Window.Title + " FPS: " + Stream.str()).c_str());
		}
	}

	delete GameObj;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}

bool init()
{
	return !(SDL_Init(SDL_INIT_EVERYTHING) != 0 || IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG || TTF_Init() != 0);
}