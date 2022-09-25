#pragma once

#include <iostream>
#include <SDL.h>
#include <vector>
#include <map>
#include <string>
#include <memory>

#include "Manager.h"
#include "Button.h"
#include "Sudoku.h"
#include "Board.h"
#include "DynamicText.h"

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

	// Main Functions

	void Tick();
	void EventLoop();
	void Render();

	// Getter Functions

	bool GetRunning() const;

private:

	// Properties

	bool m_Running;
	GameState m_State;

	// Menu Buttons

	std::unique_ptr<Button> Start;
	std::unique_ptr<Button> Settings;
	std::unique_ptr<Button> Quit;

	std::map<std::string, std::unique_ptr<Button>> m_Buttons;

	// Text Labels

	std::unique_ptr<DynamicText> Text;

	// Sudoku Grid

	std::unique_ptr<Board> Grid;
};

