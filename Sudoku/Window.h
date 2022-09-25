#pragma once

#include <iostream>
#include <SDL.h>

class Window
{
public:

	Window();
	~Window();

	// Initialise Functions

	bool InitialiseWindow();
	SDL_Renderer* CreateRenderer();

	// Window and Renderer Pointers

	static SDL_Window* m_Window;
	static SDL_Renderer* m_Renderer;

	// Properties

	static int m_Width;
	static int m_Height;

};

