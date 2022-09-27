#include "DynamicText.h"

DynamicText::DynamicText()
{
	m_Message = " ";
	m_FontSize = 16;
	m_Colour = { 90, 90, 90, 255 };

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

DynamicText::DynamicText(int PositionX, int PositionY, const std::string& Message, int FontSize, const std::string& FontPath, SDL_Color Colour)
{
	m_Message = Message;
	m_FontSize = FontSize;
	m_Colour = Colour;

	dst.x = PositionX;
	dst.y = PositionY;
	dst.w = 200;
	dst.h = 50;

	m_Font = TTF_OpenFont(FontPath.c_str(), FontSize);

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

	TTF_SizeText(m_Font, m_Message.c_str(), &dst.w, &dst.h);

	SDL_FreeSurface(m_Surface);
	SDL_RenderCopy(Window.Renderer, m_Texture, nullptr, &dst);

	if (m_Texture != nullptr)
	{
		SDL_DestroyTexture(m_Texture);
	}
}

void DynamicText::SetText(const std::string& Text)
{
	m_Message = Text;
}

void DynamicText::SetX(int PositionX)
{
	dst.x = PositionX;
}

void DynamicText::SetY(int PositionY)
{
	dst.y = PositionY;
}

SDL_Rect DynamicText::GetRect() const
{
	return dst;
}
