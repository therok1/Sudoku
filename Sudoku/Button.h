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

private:

	SDL_Texture* m_Texture;
	SDL_Rect dst;

	bool m_Selected;

};

