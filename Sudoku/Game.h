#pragma once

#include <iostream>
#include <SDL.h>
#include <vector>
#include <map>
#include <string>
#include <memory>

#include "Window.h"
#include "Button.h"
#include "Sudoku.h"
#include "Board.h"

enum GameState
{
	InGame,
	InMenu,
	InSettings
};

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

	std::map<std::string, std::unique_ptr<Button>> m_Buttons;

	std::unique_ptr<Button> Start;
	std::unique_ptr<Button> Settings;
	std::unique_ptr<Button> Quit;

	std::unique_ptr<Board> Grid;

	GameState m_State;
};

