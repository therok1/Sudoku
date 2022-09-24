#pragma once

#include <iostream>
#include <SDL.h>
#include <vector>
#include <memory>
#include <cmath>

#include "Button.h"

class Board
{
public:

	Board(Uint16 Size, SDL_Color PrimaryColour, SDL_Color SecondaryColour);
	~Board();

	void GenerateBoard();
	void Update();
	void Render();

private:

	Uint16 m_Size;

	std::vector<std::unique_ptr<Button>> m_Buttons;

};

