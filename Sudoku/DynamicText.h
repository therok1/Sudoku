#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "Window.h"

class DynamicText
{
public:

	DynamicText(int PositionX, int PositionY, const std::string& Message, int FontSize, const std::string& FontPath, SDL_Color Colour = { 255, 255, 255, 255 });
	~DynamicText();

	// Main Functions

	void Render();

private:

	TTF_Font* m_Font;
	SDL_Surface* m_Surface;
	SDL_Texture* m_Texture;
	SDL_Rect dst;

	// Properties

	std::string m_Message;
	int m_FontSize;
	SDL_Color m_Colour;

};

