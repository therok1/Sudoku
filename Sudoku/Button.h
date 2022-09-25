#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Button
{
public:

	Button(int Width, int Height);
	Button(int Width, int Height, int PositionX, int PositionY, float AnchorX = 0.f, float AnchorY = 0.f, float PercentX = 0.f, float PercentY = 0.f, const std::string& Image = "");
	~Button();

	// Main Functions

	void Update();
	void Render();
	bool MouseRelease(enum GameState State, enum GameState DesiredState);
	
	// Setter Functions

	void SetColour(SDL_Color Colour);
	void SetFocusable(bool Focusable);
	void SetX(int PositionX);
	void SetY(int PositionY);

	// Getter Functions

	bool GetFocusable() const;
	SDL_Rect GetRect() const;

private:

	SDL_Texture* m_Texture;
	SDL_Rect dst;

	// Properties

	SDL_Color m_Colour, m_HoverColour, m_ClickColour;
	bool m_Selected;
	bool m_Focusable;

};

