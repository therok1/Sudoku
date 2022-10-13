#pragma once

#include <iostream>
#include <SDL.h>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <chrono>
#include <format>

#include "Manager.h"
#include "Button.h"
#include "Sudoku.h"
#include "Board.h"
#include "DynamicText.h"
#include "SidePanel.h"

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

	Uint16 m_Mistakes;
	Uint8 m_Selected;
	bool m_Running;
	GameState m_State;
	std::chrono::steady_clock::time_point m_GameStart;

	// Menu Buttons

	std::unique_ptr<Button> m_Title;
	std::unique_ptr<Button> m_Credits;
	std::unique_ptr<Button> m_Start;
	std::unique_ptr<Button> m_Settings;
	std::unique_ptr<Button> m_Quit;

	std::map<std::string, std::unique_ptr<Button>> m_MenuButtons;

	// In-Game Buttons

	std::unique_ptr<Button> m_Title1;
	std::unique_ptr<Button> m_Timer;
	std::unique_ptr<Button> m_MouseIcon;

	// Sudoku Grid

	std::unique_ptr<Board> m_Grid;

	// Number Panel

	std::unique_ptr<SidePanel> m_SidePanel;

	// Sudoku Puzzle

	std::unique_ptr<Sudoku> m_Sudoku;

};

