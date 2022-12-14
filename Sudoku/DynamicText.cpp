#include "DynamicText.h"

DynamicText::DynamicText()
{
	m_Message = " ";
	m_FontSize = 20;
	m_FontPath = "Assets/Fonts/UniSans.ttf";
	m_Colour = { 0, 0, 0, 255 };

	dst.x = 0;
	dst.y = 0;
	dst.w = 200;
	dst.h = 50;

	m_Font = TTF_OpenFont("Assets/Fonts/UniSans.ttf", m_FontSize);

	if (m_Font == nullptr)
	{
		std::cout << "Couldn't load font: " << TTF_GetError() << std::endl;
	}
}

DynamicText::DynamicText(int PositionX, int PositionY, std::string_view Message, int FontSize, std::string_view FontPath, SDL_Color Colour)
{
	m_Message = Message;
	m_FontSize = FontSize;
	m_FontPath = FontPath;
	m_Colour = Colour;

	dst.x = PositionX;
	dst.y = PositionY;
	dst.w = 200;
	dst.h = 50;

	m_Font = TTF_OpenFont(m_FontPath.c_str(), FontSize);

	if (m_Font == nullptr)
	{
		std::cout << "Couldn't load font: " << TTF_GetError() << std::endl;
	}
}

DynamicText::~DynamicText()
{
	if (m_Texture != nullptr)
	{
		SDL_DestroyTexture(m_Texture);
	}

	if (m_Font != nullptr)
	{
		TTF_CloseFont(m_Font);
	}
}

void DynamicText::Render()
{
	m_Surface = TTF_RenderText_Blended(m_Font, m_Message.c_str(), m_Colour);

	if (m_Surface == nullptr)
	{
		std::cout << "Couldn't create surface: " << TTF_GetError() << std::endl;
	}
	
	m_Texture = SDL_CreateTextureFromSurface(Window.Renderer, m_Surface);

	if (m_Texture == nullptr)
	{
		std::cout << "Couldn't create surface: " << TTF_GetError() << std::endl;
	}

	SDL_SetTextureAlphaMod(m_Texture, m_Colour.a);

	TTF_SizeText(m_Font, m_Message.c_str(), &dst.w, &dst.h);

	SDL_FreeSurface(m_Surface);
	SDL_RenderCopy(Window.Renderer, m_Texture, nullptr, &dst);

	if (m_Texture != nullptr)
	{
		SDL_DestroyTexture(m_Texture);
	}
}

void DynamicText::SetText(std::string_view Text)
{
	m_Message = Text;
}

void DynamicText::SetFontSize(int FontSize)
{
	m_FontSize = FontSize;

	if (m_Font != nullptr)
	{
		TTF_CloseFont(m_Font);
	}

	m_Font = TTF_OpenFont(m_FontPath.c_str(), m_FontSize);
}

void DynamicText::SetFont(std::string_view FontPath)
{
	m_FontPath = FontPath;

	if (m_Font != nullptr)
	{
		TTF_CloseFont(m_Font);
	}

	m_Font = TTF_OpenFont(m_FontPath.c_str(), m_FontSize);
}

void DynamicText::SetX(int PositionX)
{
	dst.x = PositionX;
}

void DynamicText::SetY(int PositionY)
{
	dst.y = PositionY;
}

void DynamicText::SetColour(SDL_Color Colour)
{
	m_Colour = Colour;
}

void DynamicText::SetAlpha(Uint8 Alpha)
{
	m_Colour.a = Alpha;
}

SDL_Rect DynamicText::GetRect() const
{
	return dst;
}

std::string DynamicText::GetText() const
{
	return m_Message;
}
