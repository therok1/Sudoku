#include "Manager.h"

SDL_Window* Manager::Window = nullptr;
SDL_Renderer* Manager::Renderer = nullptr;

std::string Manager::Title = "SDL Desktop App";
int Manager::Width = 1280;
int Manager::Height = 720;

SDL_Point Manager::MouseCoords = SDL_Point();
Uint32 Manager::MouseButtons = Uint32();

bool Manager::InitialiseWindow(int Width, int Height, const std::string& Title)
{
	Manager::Title = Title;
	Manager::Width = Width;
	Manager::Height = Height;

	Window = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	return Window != nullptr && Renderer != nullptr;
}

void Manager::DestroyWindow()
{
	if (Renderer != nullptr) 
	{
		SDL_DestroyRenderer(Renderer);
	}

	if (Window != nullptr) 
	{
		SDL_DestroyWindow(Window);
	}
}
