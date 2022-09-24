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

	void Update();
	void Render();
	void MouseRelease();
	
	void SetColour(SDL_Color Colour);
	void SetFocusable(bool Focusable);
	void SetX(int PositionX);
	void SetY(int PositionY);

	bool GetFocusable() const;

	SDL_Rect GetRect() const;

private:

	SDL_Texture* m_Texture;
	SDL_Rect dst;

	bool m_Selected;

	// Properties

	SDL_Color m_Colour, m_HoverColour, m_ClickColour;

	bool m_Focusable;

};

