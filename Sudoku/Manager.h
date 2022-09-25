#pragma once

#include <iostream>
#include <SDL.h>
#include <string>

namespace Manager
{
	// Main Functions

	bool InitialiseWindow(int Width, int Height, const std::string& Title);
	void DestroyWindow();

	// Window and Renderer Pointers

	extern SDL_Window* Window;
	extern SDL_Renderer* Renderer;

	// Window Properties

	extern std::string Title;
	extern int Width;
	extern int Height;

	// Mouse Properties

	extern SDL_Point MouseCoords;
	extern Uint32 MouseButtons;
}

