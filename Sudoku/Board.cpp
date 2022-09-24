#include "Board.h"

Board::Board(Uint16 Size, SDL_Color PrimaryColour, SDL_Color SecondaryColour)
{
	m_Size = sqrt(Size);

	for (int i = 0; i < pow(m_Size, 2); i++)
	{
		m_Buttons.push_back(std::make_unique<Button>(50, 50));

		if (i % 2)
		{
			m_Buttons[i]->SetColour(PrimaryColour);
		}
		else
		{
			m_Buttons[i]->SetColour(SecondaryColour);
		}
	}

	m_Buttons.shrink_to_fit();
}

Board::~Board()
{

}

void Board::GenerateBoard()
{
	int Index = 0;

	for (int i = 0; i < m_Size; i++)
	{
		for (int j = 0; j < m_Size; j++)
		{
			m_Buttons[Index]->SetX(m_Buttons[i]->GetRect().w * i);
			m_Buttons[Index]->SetY(m_Buttons[i]->GetRect().w * j);
			
			Index++;
		}
	}
}

void Board::Update()
{
	for (auto& Button : m_Buttons)
	{
		Button->Update();
	}
}

void Board::Render()
{
	for (auto& Button : m_Buttons)
	{
		Button->Render();
	}
}
