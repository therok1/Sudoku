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

	void ConstructMenuUI();
	void ConstructGameUI();

	void RenderMenuUI();
	void RenderGameUI();

	void UpdateMenuUI();
	void UpdateGameUI();

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

	std::map<std::string, std::unique_ptr<Button>> m_MenuElements;

	// In-Game Buttons

	std::map<std::string, std::unique_ptr<Button>> m_GameElements;

	// Sudoku Grid

	std::unique_ptr<Board> m_Grid;

	// Number Panel

	std::unique_ptr<SidePanel> m_SidePanel;

	// Sudoku Puzzle

	std::unique_ptr<Sudoku> m_Sudoku;

};

