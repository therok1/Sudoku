#pragma once

#include <iostream>
#include <SDL.h>
#include <vector>
#include <memory>
#include <cmath>

#include "Button.h"
#include "Manager.h"

struct Vector2D
{
	float X, Y;
};

class Board
{
public:

	Board(Uint16 Size, SDL_Color PrimaryColour, SDL_Color SecondaryColour);
	~Board();

	// Main Functions

	void GenerateBoard();
	void Update();
	void Render();

	// Setter Functions

	void SetX(int PositionX, bool A = false, float PercentX = 0.0f);
	void SetY(int PositionY, bool A = false, float PercentY = 0.0f);
	void SetAnchorPoint(float AnchorX, float AnchorY);

private:

	std::vector<std::unique_ptr<Button>> m_Buttons;
	
	// Properties

	Uint16 m_Size;
	Vector2D m_AnchorPoint;
	Vector2D m_Position;
	Vector2D m_SqSize;

};

