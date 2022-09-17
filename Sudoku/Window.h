#pragma once

#include <iostream>
#include <SDL.h>

class Window
{
public:

	Window();
	~Window();

	bool InitialiseWindow();

	SDL_Renderer* CreateRenderer();

	static SDL_Window* m_Window;
	static SDL_Renderer* m_Renderer;

	static int m_Width;
	static int m_Height;

};

