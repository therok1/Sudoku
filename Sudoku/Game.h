#pragma once

#include <iostream>
#include <SDL.h>
#include <vector>
#include <memory>

#include "Window.h"
#include "Button.h"
#include "Sudoku.h"
#include "Board.h"

class Game
{
public:

	Game();
	~Game();

	void Tick();
	void EventLoop();
	void Render();

	bool GetRunning() const;

	static SDL_Point m_MouseCoords;

	static Uint32 m_MouseButtons;

private:

	bool m_Running;

	std::vector<std::unique_ptr<Button>> m_Buttons;

	std::unique_ptr<Button> Start;
	std::unique_ptr<Board> Grid;
};

