#pragma once

#include <iostream>
#include <SDL.h>

#include "Button.h"

class Game
{
public:

	Game();

	void Tick();
	void EventLoop();
	void Render();

	bool GetRunning();

	static SDL_Point m_MouseCoords;

	static Uint32 m_MouseButtons;

private:

	bool m_Running;

	Button* Start;
};

