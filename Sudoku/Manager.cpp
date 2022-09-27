#include "Manager.h"

Manager::MWindow Window = Manager::MWindow();
Manager::MMouse Mouse = Manager::MMouse();
Manager::MSettings Settings = Manager::MSettings();

bool Manager::InitialiseWindow(int Width, int Height, const std::string& Title)
{
	Window.Title = Title;
	Window.Width = Width;
	Window.Height = Height;

	Window.Window = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);
	Window.Renderer = SDL_CreateRenderer(Window.Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	return Window.Window != nullptr && Window.Renderer != nullptr;
}

void Manager::DestroyWindow()
{
	if (Window.Renderer != nullptr) 
	{
		SDL_DestroyRenderer(Window.Renderer);
	}

	if (Window.Window != nullptr) 
	{
		SDL_DestroyWindow(Window.Window);
	}
}
