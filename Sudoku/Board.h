#pragma once

#include <iostream>
#include <SDL.h>
#include <vector>
#include <memory>
#include <cmath>
#include <array>

#include "Button.h"
#include "Manager.h"
#include "Vector2D.h"

class Board
{
public:

	Board(Uint16 Size, SDL_Color PrimaryColour, SDL_Color SecondaryColour);
	~Board();

	// Main Functions

	void GenerateBoard();
	void GenerateSolution(const std::array<std::array<int, 9>, 9>& Sudoku);
	void FillBoard(const std::array<std::array<int, 9>, 9>& Sudoku, const std::array<std::array<int, 9>, 9>& SudokuSolution);
	void FillCell(enum GameState State, enum GameState DesiredState, Uint8 Selected, Uint16& Mistakes);
	void Update();
	void Render();

	// Setter Functions

	void SetX(int PositionX, bool A = false, float PercentX = 0.0f);
	void SetY(int PositionY, bool A = false, float PercentY = 0.0f);
	void SetAnchorPoint(float AnchorX, float AnchorY);

private:

	std::vector<std::unique_ptr<Button>> m_Buttons;
	std::vector<SDL_Rect> m_VerticalLines;
	std::vector<SDL_Rect> m_HorizontalLines;
	std::array<std::array<int, 9>, 9> m_Sudoku;
	std::array<std::array<int, 9>, 9> m_SudokuSolution;
	
	// Properties

	Uint16 m_Size;
	Vector2D m_AnchorPoint;
	Vector2D m_Position;
	Vector2D m_SqSize;
	SDL_Color m_PrimaryColour;
	SDL_Color m_SecondaryColour;

};

