#include "Button.h"

#include "Game.h"
#include "Manager.h"

Button::Button(int Width, int Height)
{
	m_Selected = false;
	m_Texture = nullptr;

	m_Colour = { 0, 0, 0, 255 };
	m_HoverColour = { 0, 0, 0, 255 };
	m_ClickColour = { 0, 0, 0, 255 };
	m_Focusable = true;

	dst.w = Width;
	dst.h = Height;
	dst.x = 0;
	dst.y = 0;
}

Button::Button(int Width, int Height, int PositionX, int PositionY, float AnchorX, float AnchorY, float PercentX, float PercentY, const std::string& Image)
{
	m_Selected = false;
	m_Texture = nullptr;

	m_Colour = { 0, 0, 0, 255 };
	m_HoverColour = { 0, 0, 0, 255 };
	m_ClickColour = { 0, 0, 0, 255 };
	m_Focusable = true;

	if (!Image.empty())
	{
		static SDL_Texture* Texture = IMG_LoadTexture(Manager::Renderer, Image.c_str());
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
		dst.x = static_cast<int>(Manager::Width * PercentX) - static_cast<int>(dst.w * AnchorX);
		dst.y = static_cast<int>(Manager::Height * PercentY) - static_cast<int>(dst.h * AnchorY);
	}
}

Button::~Button()
{
	if (m_Texture)
	{
		SDL_DestroyTexture(m_Texture);
	}
}

void Button::Update()
{
	if (m_Focusable)
	{
		if (SDL_PointInRect(&Manager::MouseCoords, &dst))
		{
			m_Selected = true;
		}
		else
		{
			m_Selected = false;
		}
	}
}

void Button::Render()
{
	if (m_Texture != nullptr)
	{
		SDL_RenderCopy(Manager::Renderer, m_Texture, nullptr, &dst);
	}
	else
	{
		SDL_SetRenderDrawColor(Manager::Renderer, m_Colour.r, m_Colour.g, m_Colour.b, m_Colour.a);
		
		if (m_Selected)
		{
			SDL_SetRenderDrawColor(Manager::Renderer, m_HoverColour.r, m_HoverColour.g, m_HoverColour.b, m_HoverColour.a);

			// If left mouse click is pressed
			if ((Manager::MouseButtons & SDL_BUTTON_LMASK) != 0)
			{
				SDL_SetRenderDrawColor(Manager::Renderer, m_ClickColour.r, m_ClickColour.g, m_ClickColour.b, m_ClickColour.a);
			}
		}
		
		SDL_RenderFillRect(Manager::Renderer, &dst);
		SDL_SetRenderDrawColor(Manager::Renderer, 0, 0, 0, 255);
	}
}

bool Button::MouseRelease(GameState State, GameState DesiredState)
{
	return (State == DesiredState) ? SDL_PointInRect(&Manager::MouseCoords, &dst) : false;
}

void Button::SetColour(SDL_Color Colour)
{
	m_Colour = Colour;
	m_HoverColour = Colour;
	m_ClickColour = Colour;

	m_HoverColour.r = m_HoverColour.r * 0.9f;
	m_HoverColour.g = m_HoverColour.g * 0.9f;
	m_HoverColour.b = m_HoverColour.b * 0.9f;

	m_ClickColour.r = m_ClickColour.r * 0.75f;
	m_ClickColour.g = m_ClickColour.g * 0.75f;
	m_ClickColour.b = m_ClickColour.b * 0.75f;
}

void Button::SetFocusable(bool Focusable)
{
	m_Focusable = Focusable;
}

void Button::SetX(int PositionX)
{
	dst.x = PositionX;
}

void Button::SetY(int PositionY)
{
	dst.y = PositionY;
}

bool Button::GetFocusable() const
{
	return m_Focusable;
}

SDL_Rect Button::GetRect() const
{
	return dst;
}
