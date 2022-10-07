#include "Board.h"

Board::Board(Uint16 Size, SDL_Color PrimaryColour, SDL_Color SecondaryColour)
{
	m_Size = sqrt(Size);
	m_PrimaryColour = PrimaryColour;
	m_SecondaryColour = SecondaryColour;

	m_AnchorPoint.SetX(0);
	m_AnchorPoint.SetY(0);
	m_Position.SetX(0);
	m_Position.SetY(0);
	m_SqSize.SetX(50);
	m_SqSize.SetY(50);

	int Index = 0;

	for (int i = 0; i < m_Size; i++)
	{
		for (int j = 0; j < m_Size; j++)
		{
			m_Buttons.push_back(std::make_unique<Button>(m_SqSize.GetX(), m_SqSize.GetY()));

			if (i % 2 == j % 2)
			{
				m_Buttons[Index]->SetColour(PrimaryColour);
				m_Buttons[Index]->SetTextColour({ 0, 150, 201, 255 });
			}
			else
			{
				m_Buttons[Index]->SetColour(SecondaryColour);
				m_Buttons[Index]->SetTextColour({ 0, 108, 145, 255 });
			}

			m_Buttons[Index]->SetText(std::to_string(Index));

			Index++;
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

	for (int j = 0; j < m_Size; j++)
	{
		for (int i = 0; i < m_Size; i++)
		{
			m_Buttons[Index]->SetX(m_Buttons[i]->GetRect().w * i);
			m_Buttons[Index]->SetY(m_Buttons[i]->GetRect().h * j);

			Index++;
		}
	}
}

void Board::FillBoard(const std::array<std::array<int, 9>, 9>& Sudoku)
{
	int Index = 0;

	for (int j = 0; j < m_Size; j++)
	{
		for (int i = 0; i < m_Size; i++)
		{
			m_Buttons[Index]->SetText((Sudoku[j][i] == 0) ? " " : std::to_string(Sudoku[j][i]));

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

void Board::SetX(int PositionX, bool A, float PercentX)
{
	int Index = 0;

	for (int j = 0; j < m_Size; j++)
	{
		for (int i = 0; i < m_Size; i++)
		{
			if (!A)
			{
				m_Buttons[Index]->SetX((m_Buttons[i]->GetRect().w * i) + (PositionX - static_cast<int>(m_Buttons[i]->GetRect().w * m_Size * m_AnchorPoint.GetX())));
				m_Position.SetX(PositionX - static_cast<int>(m_Buttons[i]->GetRect().w * m_Size * m_AnchorPoint.GetX()));
			}
			else
			{
				m_Buttons[Index]->SetX((m_Buttons[i]->GetRect().w * i) + static_cast<int>(Window.Width * PercentX) - static_cast<int>(m_Buttons[i]->GetRect().w * m_Size * m_AnchorPoint.GetX()));
				m_Position.SetX(static_cast<int>(Window.Width * PercentX) - static_cast<int>(m_Buttons[i]->GetRect().w * m_Size * m_AnchorPoint.GetX()));
			}

			Index++;
		}
	}
}

void Board::SetY(int PositionY, bool A, float PercentY)
{
	int Index = 0;

	for (int j = 0; j < m_Size; j++)
	{
		for (int i = 0; i < m_Size; i++)
		{
			if (!A)
			{
				m_Buttons[Index]->SetY((m_Buttons[i]->GetRect().h * j) + (PositionY - static_cast<int>(m_Buttons[i]->GetRect().h * m_Size * m_AnchorPoint.GetY())));
				m_Position.SetY(PositionY - static_cast<int>(m_Buttons[i]->GetRect().h * m_Size * m_AnchorPoint.GetY()));
			}
			else
			{
				m_Buttons[Index]->SetY((m_Buttons[i]->GetRect().h * j) + static_cast<int>(Window.Height * PercentY) - static_cast<int>(m_Buttons[i]->GetRect().h * m_Size * m_AnchorPoint.GetY()));
				m_Position.SetY(static_cast<int>(Window.Height * PercentY) - static_cast<int>(m_Buttons[i]->GetRect().h * m_Size * m_AnchorPoint.GetY()));
			}

			Index++;
		}
	}
}

void Board::SetAnchorPoint(float AnchorX, float AnchorY)
{
	m_AnchorPoint.SetX(AnchorX);
	m_AnchorPoint.SetY(AnchorY);
	
	SetX(m_Position.GetX());
	SetY(m_Position.GetY());
}