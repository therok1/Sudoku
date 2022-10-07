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


private:

	std::vector<int> m_Numbers;
	std::vector<std::unique_ptr<Button>> m_Buttons;

	// Properties

	Vector2D m_AnchorPoint;
	Vector2D m_Position;
	Vector2D m_SqSize;
};

