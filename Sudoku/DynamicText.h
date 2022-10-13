#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "Manager.h"

class DynamicText
{
public:

	DynamicText();
	DynamicText(int PositionX, int PositionY, const std::string& Message, int FontSize, const std::string& FontPath, SDL_Color Colour = { 0, 0, 0, 255 });
	~DynamicText();

	// Main Functions

	void Render();

	// Setter Functions

	void SetText(const std::string& Text);
	void SetFontSize(int FontSize);
	void SetFont(const std::string& FontPath);
	void SetX(int PositionX);
	void SetY(int PositionY);
	void SetColour(SDL_Color Colour);
	void SetAlpha(Uint8 Alpha);

	// Getter Functions

	SDL_Rect GetRect() const;
	std::string GetText() const;

private:

	TTF_Font* m_Font;
	SDL_Surface* m_Surface;
	SDL_Texture* m_Texture;
	SDL_Rect dst;

	// Properties

	std::string m_Message;
	int m_FontSize;
	std::string m_FontPath;
	SDL_Color m_Colour;

};

