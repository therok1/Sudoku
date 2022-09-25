#include "DynamicText.h"

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
	SDL_DestroyTexture(m_Texture);
	TTF_CloseFont(m_Font);
}

void DynamicText::Render()
{
	m_Surface = TTF_RenderText_Blended(m_Font, m_Message.c_str(), m_Colour);

	if (m_Surface == nullptr)
	{
		std::cout << "Couldn't create surface: " << TTF_GetError() << std::endl;
	}
	
	m_Texture = SDL_CreateTextureFromSurface(Manager::Renderer, m_Surface);

	if (m_Texture == nullptr)
	{
		std::cout << "Couldn't create surface: " << TTF_GetError() << std::endl;
	}

	TTF_SizeText(m_Font, m_Message.c_str(), &dst.w, &dst.h);

	SDL_FreeSurface(m_Surface);
	SDL_RenderCopy(Manager::Renderer, m_Texture, nullptr, &dst);

	if (m_Texture != nullptr)
	{
		SDL_DestroyTexture(m_Texture);
	}
}
