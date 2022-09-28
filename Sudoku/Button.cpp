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

	m_Text = std::make_unique<DynamicText>();

	Refresh();
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
		static SDL_Texture* Texture = IMG_LoadTexture(Window.Renderer, Image.c_str());
		m_Texture = Texture;
	}

	dst.w = Width;
	dst.h = Height;

	if (PercentX == 0.0f && PercentY == 0.0f)
	{
		dst.x = PositionX - static_cast<int>(dst.w * AnchorX);
		dst.y = PositionY - static_cast<int>(dst.h * AnchorY);
	}
	else if (PercentY == 0.0f && PercentX != 0.0f)
	{
		dst.x = static_cast<int>(Window.Width * PercentX) - static_cast<int>(dst.w * AnchorX);
		dst.y = PositionY - static_cast<int>(dst.h * AnchorY);
	}
	else if (PercentX == 0.0f && PercentY != 0.0f)
	{
		dst.x = PositionX - static_cast<int>(dst.w * AnchorX);
		dst.y = static_cast<int>(Window.Height * PercentY) - static_cast<int>(dst.h * AnchorY);
	}
	else
	{
		dst.x = static_cast<int>(Window.Width * PercentX) - static_cast<int>(dst.w * AnchorX);
		dst.y = static_cast<int>(Window.Height * PercentY) - static_cast<int>(dst.h * AnchorY);
	}

	m_Text = std::make_unique<DynamicText>();

	Refresh();
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
		if (SDL_PointInRect(&Mouse.MouseCoords, &dst))
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
		SDL_RenderCopy(Window.Renderer, m_Texture, nullptr, &dst);
	}
	else
	{
		SDL_SetRenderDrawColor(Window.Renderer, m_Colour.r, m_Colour.g, m_Colour.b, m_Colour.a);

		if (m_Selected)
		{
			SDL_SetRenderDrawColor(Window.Renderer, m_HoverColour.r, m_HoverColour.g, m_HoverColour.b, m_HoverColour.a);

			// If left mouse click is pressed
			if ((Mouse.MouseButtons & SDL_BUTTON_LMASK) != 0)
			{
				SDL_SetRenderDrawColor(Window.Renderer, m_ClickColour.r, m_ClickColour.g, m_ClickColour.b, m_ClickColour.a);
			}
		}

		if (m_Colour.a != 0)
		{
			SDL_RenderFillRect(Window.Renderer, &dst);
		}

		m_Text->Render();
	}
}

void Button::Refresh()
{
	Render();

	m_Text->SetX(dst.x + static_cast<int>(dst.w * 0.5) - static_cast<int>(m_Text->GetRect().w * 0.5));
	m_Text->SetY(dst.y + static_cast<int>(dst.h * 0.5) - static_cast<int>(m_Text->GetRect().h * 0.5));
}

bool Button::MouseRelease(enum GameState State, enum GameState DesiredState)
{
	return ((State == DesiredState) && m_Focusable) ? SDL_PointInRect(&Mouse.MouseCoords, &dst) : false;
}

void Button::SetText(const std::string& Text)
{
	m_Text->SetText(Text);

	Refresh();
}

void Button::SetFontSize(int FontSize)
{
	m_Text->SetFontSize(FontSize);

	Refresh();
}

void Button::SetFont(const std::string& FontPath)
{
	m_Text->SetFont(FontPath);

	Refresh();
}

void Button::SetFocusable(bool Focusable)
{
	m_Focusable = Focusable;
}

void Button::SetX(int PositionX)
{
	dst.x = PositionX;

	m_Text->SetX(dst.x + static_cast<int>(dst.w * 0.5) - static_cast<int>(m_Text->GetRect().w * 0.5));
}

void Button::SetY(int PositionY)
{
	dst.y = PositionY;

	m_Text->SetY(dst.y + static_cast<int>(dst.h * 0.5) - static_cast<int>(m_Text->GetRect().h * 0.5));
}

void Button::SetColour(SDL_Color Colour)
{
	m_Colour = Colour;
	m_HoverColour = Colour;
	m_ClickColour = Colour;

	m_HoverColour.r *= 0.98f;
	m_HoverColour.g *= 0.98f;
	m_HoverColour.b *= 0.98f;

	m_ClickColour.r *= 0.95f;
	m_ClickColour.g *= 0.95f;
	m_ClickColour.b *= 0.95f;
}

void Button::SetTextColour(SDL_Color Colour)
{
	m_Text->SetColour(Colour);
}

bool Button::GetFocusable() const
{
	return m_Focusable;
}

SDL_Rect Button::GetRect() const
{
	return dst;
}
