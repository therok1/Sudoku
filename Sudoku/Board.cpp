#include "Board.h"
#include "Game.h"

Board::Board(Uint16 Size, SDL_Color PrimaryColour, SDL_Color SecondaryColour)
{
	m_Sudoku = { 0 };
	m_SudokuSolution = { 0 };

	m_Size = sqrt(Size);

	m_PrimaryColour = PrimaryColour;
	m_SecondaryColour = SecondaryColour;

	m_AnchorPoint.SetX(0);
	m_AnchorPoint.SetY(0);

	m_Position.SetX(0);
	m_Position.SetY(0);

	m_SqSize.SetX(50);
	m_SqSize.SetY(50);

	m_Buttons.reserve(Size);
	m_VerticalLines.reserve((m_Size / 3) - 1);
	m_HorizontalLines.reserve((m_Size / 3) - 1);

	int Index = 0;

	for (int i = 0; i < m_Size; i++)
	{
		for (int j = 0; j < m_Size; j++)
		{
			m_Buttons.push_back(std::make_unique<Button>(m_SqSize.GetX(), m_SqSize.GetY()));

			if (i % 2 == j % 2)
			{
				m_Buttons[Index]->SetColour(PrimaryColour);
			}
			else
			{
				m_Buttons[Index]->SetColour(SecondaryColour);
			}

			m_Buttons[Index]->SetText(std::to_string(Index));
			m_Buttons[Index]->SetTextColour(SDL_Color(0, 0, 0, 255));

			Index++;
		}
	}

	for (int i = 1; i <= (m_Size / 3) - 1; i++)
	{
		SDL_Rect Line = { i * 3 * m_SqSize.GetX() - 1, 0, 2, m_Size * m_SqSize.GetY() };
		m_VerticalLines.push_back(Line);
	}

	for (int i = 1; i <= (m_Size / 3) - 1; i++)
	{
		SDL_Rect Line = { 0, i * 3 * m_SqSize.GetY() - 1, m_Size * m_SqSize.GetX(), 2 };
		m_HorizontalLines.push_back(Line);
	}
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

void Board::GenerateSolution(const std::array<std::array<int, 9>, 9>& Sudoku)
{
	m_SudokuSolution = Sudoku;
}

void Board::FillBoard(const std::array<std::array<int, 9>, 9>& Sudoku, const std::array<std::array<int, 9>, 9>& SudokuSolution)
{
	int Index = 0;

	for (int j = 0; j < m_Size; j++)
	{
		for (int i = 0; i < m_Size; i++)
		{
			m_Buttons[Index]->SetText((Sudoku[j][i] == 0) ? " " : std::to_string(Sudoku[j][i]));
			m_Buttons[Index]->SetTextColour(SDL_Color(0, 0, 0, 255));

			Index++;
		}
	}

	m_Sudoku = Sudoku;
	m_SudokuSolution = SudokuSolution;
}

void Board::FillCell(enum GameState State, enum GameState DesiredState, Uint8 Selected, Uint16& Mistakes)
{
	int Index = 0;

	for (int j = 0; j < m_Size; j++)
	{
		for (int i = 0; i < m_Size; i++)
		{
			if (m_Buttons[Index]->MouseRelease(State, DesiredState))
			{
				if (m_Sudoku[j][i] == 0 || m_Sudoku[j][i] != m_SudokuSolution[j][i])
				{
					m_Buttons[Index]->SetText(Selected ? std::to_string(Selected) : " ");
					m_Sudoku[j][i] = Selected;

					if (m_SudokuSolution[j][i] != Selected)
					{
						m_Buttons[Index]->SetTextColour(SDL_Color(255, 54, 54, 255)); // Mark incorrect field with red

						if (Selected)
						{
							Mistakes++;
						}
					}
					else
					{
						m_Buttons[Index]->SetTextColour(SDL_Color(0, 0, 0, 255));
					}
				}
			}

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

	for (auto& VerticalLine : m_VerticalLines)
	{
		SDL_SetRenderDrawColor(Window.Renderer, 200, 200, 200, 255);
		SDL_RenderFillRect(Window.Renderer, &VerticalLine);
	}

	for (auto& HorizontalLine : m_HorizontalLines)
	{
		SDL_SetRenderDrawColor(Window.Renderer, 200, 200, 200, 255);
		SDL_RenderFillRect(Window.Renderer, &HorizontalLine);
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
	
	for (int i = 0; i < m_VerticalLines.size(); i++)
	{
		m_VerticalLines[i].x = m_Buttons[0]->GetRect().x + (i + 1) * 3 * m_SqSize.GetX() - 1;
	}
	
	for (int i = 0; i < m_HorizontalLines.size(); i++)
	{
		m_HorizontalLines[i].x = m_Buttons[0]->GetRect().x;
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

	for (int i = 0; i < m_VerticalLines.size(); i++)
	{
		m_VerticalLines[i].y = m_Buttons[0]->GetRect().y;
	}

	for (int i = 0; i < m_HorizontalLines.size(); i++)
	{
		m_HorizontalLines[i].y = m_Buttons[0]->GetRect().y + (i + 1) * 3 * m_SqSize.GetY() - 1;
	}
}

void Board::SetAnchorPoint(float AnchorX, float AnchorY)
{
	m_AnchorPoint.SetX(AnchorX);
	m_AnchorPoint.SetY(AnchorY);
	
	SetX(m_Position.GetX());
	SetY(m_Position.GetY());
}

const std::array<std::array<int, 9>, 9>& Board::GetSudoku() const
{
	return m_Sudoku;
}
