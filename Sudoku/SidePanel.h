#pragma once

#include <iostream>
#include <SDL.h>
#include <vector>
#include <memory>

#include "Button.h"
#include "Manager.h"
#include "Vector2D.h"

class SidePanel
{
public:

	SidePanel();

	// Main Functions

	void GeneratePanel();
	void Update();
	void Render();
	void Select(enum GameState State, enum GameState DesiredState, int& Selected);

	// Setter Functions

	void SetX(int PositionX, bool A = false, float PercentX = 0.0f);
	void SetY(int PositionY, bool A = false, float PercentY = 0.0f);
	void SetAnchorPoint(float AnchorX, float AnchorY);


private:

	std::vector<int> m_Numbers;
	std::vector<std::unique_ptr<Button>> m_Buttons;

	// Properties

	int m_Padding;
	Vector2D m_AnchorPoint;
	Vector2D m_Position;
	Vector2D m_SqSize;
};

