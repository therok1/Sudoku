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

struct Animation
{
	bool Active;
	Uint32 StartTime;
	Uint32 CurrentTime;
	Uint32 Duration;
	SDL_Color Start;
	SDL_Color End;
	SDL_Color Result;

	Animation(Uint32 _Duration, SDL_Color _Start, SDL_Color _End)
	{
		Active = false;
		StartTime = SDL_GetTicks();
		CurrentTime = SDL_GetTicks();
		Duration = _Duration;
		Start = _Start;
		End = _End;
		Result = _Start;
	}
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

	std::unique_ptr<Button> m_Start;
	std::unique_ptr<Button> m_Settings;
	std::unique_ptr<Button> m_Quit;

	std::map<std::string, std::unique_ptr<Button>> m_Buttons;

	// Text Labels

	std::unique_ptr<DynamicText> m_Text;

	// Sudoku Grid

	std::unique_ptr<Board> m_Grid;

	// Animations

	std::unique_ptr<Animation> BackgroundAnim;

};

