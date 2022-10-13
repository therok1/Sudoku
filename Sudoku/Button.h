#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <memory>

#include "DynamicText.h"

class Button
{
public:

	Button() = default;
	Button(int Width, int Height);
	Button(int Width, int Height, int PositionX, int PositionY, float AnchorX = 0.f, float AnchorY = 0.f, float PercentX = 0.f, float PercentY = 0.f, const std::string& Image = "");
	~Button();

	// Main Functions

	void Update();
	void Render();
	void Refresh();
	bool MouseRelease(enum GameState State, enum GameState DesiredState);
	
	// Setter Functions

	void SetText(const std::string& Text);
	void SetFontSize(int FontSize);
	void SetFont(const std::string& FontPath);
	void SetFocusable(bool Focusable);
	void SetX(int PositionX);
	void SetY(int PositionY);
	void SetColour(SDL_Color Colour);
	void SetTextColour(SDL_Color Colour);
	void SetTextAlpha(Uint8 Alpha);
	void SetFitText();

	// Getter Functions

	bool GetFocusable() const;
	SDL_Rect GetRect() const;
	std::string GetText() const;

private:

	SDL_Texture* m_Texture;
	SDL_Rect dst;
	std::unique_ptr<DynamicText> m_Text;

	// Properties

	SDL_Color m_Colour, m_HoverColour, m_ClickColour;
	bool m_Selected;
	bool m_Focusable;

};

