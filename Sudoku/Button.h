#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Button
{
public:

	Button(int Width, int Height, int PositionX, int PositionY, float AnchorX = 0.f, float AnchorY = 0.f, float PercentX = 0.f, float PercentY = 0.f, const std::string& Image = "");
	~Button();

	void Update();
	void Render();
	
	void SetColour(SDL_Color Colour);
	void SetFocusable(bool Focusable);

private:

	SDL_Texture* m_Texture;
	SDL_Rect dst;

	bool m_Selected;

	// Properties

	SDL_Color m_Colour, m_HoverColour;

	bool m_Focusable;

};

