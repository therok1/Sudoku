#include "Button.h"

#include "Game.h"
#include "Window.h"

Button::Button(int Width, int Height, int PositionX, int PositionY, float AnchorX, float AnchorY, float PercentX, float PercentY, const std::string& Image)
{
	m_Selected = false;

	if (!Image.empty())
	{
		static SDL_Texture* Texture = IMG_LoadTexture(Window::m_Renderer, Image.c_str());
		m_Texture = Texture;
	}

	if (PercentX == 0.f && PercentY == 0.f)
	{
		dst.w = Width;
		dst.h = Height;
		dst.x = PositionX - static_cast<int>(dst.w * AnchorX);
		dst.y = PositionY - static_cast<int>(dst.h * AnchorY);
	}
	else
	{
		dst.w = Width;
		dst.h = Height;
		dst.x = static_cast<int>(Window::m_Width * PercentX) - static_cast<int>(dst.w * AnchorX);
		dst.y = static_cast<int>(Window::m_Height * PercentY) - static_cast<int>(dst.h * AnchorY);
	}
}

Button::~Button()
{

}

void Button::Update()
{
	if (SDL_PointInRect(&Game::m_MouseCoords, &dst))
	{
		m_Selected = true;
	}
	else
	{
		m_Selected = false;
	}
}

void Button::Render()
{
	if (m_Texture != nullptr)
	{
		SDL_RenderCopy(Window::m_Renderer, m_Texture, nullptr, &dst);
	}
	else
	{
		SDL_SetRenderDrawColor(Window::m_Renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(Window::m_Renderer, &dst);
		SDL_SetRenderDrawColor(Window::m_Renderer, 255, 255, 255, 255);
	}
}
