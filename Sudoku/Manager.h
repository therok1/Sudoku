#pragma once

#include <iostream>
#include <SDL.h>
#include <string>

namespace Manager
{
	// Main Functions

	bool InitialiseWindow(int Width, int Height, const std::string& Title);
	void DestroyWindow();

	struct MWindow
	{
		SDL_Window* Window = nullptr;
		SDL_Renderer* Renderer = nullptr;

		std::string Title = "SDL Desktop App";
		int Width = 1280;
		int Height = 720;

		float FPS = 0;
	};

	struct MMouse
	{
		SDL_Point MouseCoords = SDL_Point();
		Uint32 MouseButtons = Uint32();
	};

	struct MSettings
	{
		bool DarkMode = false;
	};
}

extern Manager::MWindow Window;
extern Manager::MMouse Mouse;
extern Manager::MSettings Settings;