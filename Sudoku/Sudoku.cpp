#include "Sudoku.h"

int Random(int MaxRange)
{
	return rand() % MaxRange;
}

bool FindUnassignedLocation(const std::array<std::array<int, 9>, 9>& m_Grid, int& Row, int& Col)
{
	for (Row = 0; Row < 9; Row++)
	{
		for (Col = 0; Col < 9; Col++)
		{
			if (m_Grid[Row][Col] == UNASSIGNED)
			{
				return true;
			}
		}
	}

	return false;
}

bool UsedInRow(const std::array<std::array<int, 9>, 9>& m_Grid, int Row, int Num)
{
	for (int Col = 0; Col < 9; Col++)
	{
		if (m_Grid[Row][Col] == Num)
		{
			return true;
		}
	}

	return false;
}

bool UsedInColumn(const std::array<std::array<int, 9>, 9>& m_Grid, int Col, int Num)
{
	for (int Row = 0; Row < 9; Row++)
	{
		if (m_Grid[Row][Col] == Num)
		{
			return true;
		}
	}

	return false;
}

bool UsedInBox(const std::array<std::array<int, 9>, 9>& m_Grid, int BoxStartRow, int BoxStartCol, int Num)
{
	for (int Row = 0; Row < 3; Row++)
	{
		for (int Col = 0; Col < 3; Col++)
		{
			if (m_Grid[Row + BoxStartRow][Col + BoxStartCol] == Num)
			{
				return true;
			}
		}
	}

	return false;
}

bool IsSafe(const std::array<std::array<int, 9>, 9>& m_Grid, int Row, int Col, int Num)
{
	return !UsedInRow(m_Grid, Row, Num) && !UsedInColumn(m_Grid, Col, Num) && !UsedInBox(m_Grid, Row - Row % 3, Col - Col % 3, Num);
}

void Sudoku::FillEmptyDiagonalBox(int Index)
{
	int Start = Index * 3;

	std::random_shuffle(std::begin(m_Numbers), std::end(m_Numbers), Random);

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			m_Grid[Start + i][Start + j] = m_Numbers[i * 3 + j];
		}
	}
}

void Sudoku::CreateSeed()
{
	FillEmptyDiagonalBox(0);
	FillEmptyDiagonalBox(1);
	FillEmptyDiagonalBox(2);

	SolveGrid();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			m_SolutionGrid[i][j] = m_Grid[i][j];
		}
	}
}

Sudoku::Sudoku()
{
	m_DifficultyLevel = 0;
	m_Grid = { 0 };
	m_GridPosition = { 0 };
	m_Numbers = { 0 };
	m_SolutionGrid = { 0 };

	for (int i = 0; i < 81; i++)
	{
		m_GridPosition[i] = i;
	}

	std::random_shuffle(std::begin(m_GridPosition), std::end(m_GridPosition), Random);

	for (int i = 0; i < 9; i++)
	{
		m_Numbers[i] = i + 1;
	}

	std::random_shuffle(std::begin(m_Numbers), std::end(m_Numbers), Random);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			m_Grid[i][j] = 0;
		}
	}

	m_GridStatus = true;
}

Sudoku::Sudoku(const std::string& GridString, bool RowMajor)
{
	m_DifficultyLevel = 0;
	m_Grid = { 0 };
	m_GridPosition = { 0 };
	m_Numbers = { 0 };
	m_SolutionGrid = { 0 };

	if (GridString.length() != 81)
	{
		m_GridStatus = false;

		return;
	}

	for (int i = 0; i < 81; ++i)
	{
		int Current = GridString[i] - '0';

		if (!((Current == UNASSIGNED) || (Current > 0 && Current < 10)))
		{
			m_GridStatus = false;

			return;
		}

		if (RowMajor)
		{
			m_Grid[i / 9][i % 9] = Current;
		}
		else
		{
			m_Grid[i % 9][i / 9] = Current;
		}
	}

	for (int Col = 0; Col < 9; ++Col)
	{
		std::array<bool, 10> Nums = { false };

		for (int Row = 0; Row < 9; ++Row)
		{
			int Current = m_Grid[Row][Col];

			if (Current != UNASSIGNED && Nums[Current] == true)
			{
				m_GridStatus = false;

				return;
			}

			Nums[Current] = true;
		}
	}

	for (int Row = 0; Row < 9; ++Row)
	{
		std::array<bool, 10> Nums = { false };

		for (int Col = 0; Col < 9; ++Col)
		{
			int Current = m_Grid[Row][Col];

			if (Current != UNASSIGNED && Nums[Current] == true)
			{
				m_GridStatus = false;

				return;
			}

			Nums[Current] = true;
		}
	}

	for (int Block = 0; Block < 9; ++Block)
	{
		std::array<bool, 9> Nums = { false };

		for (int Cell = 0; Cell < 9; ++Cell)
		{
			int Current = m_Grid[(static_cast<int>(Block / 3)) * 3 + (Cell / 3)][(static_cast<int>(Block % 3)) * 3 + (Cell % 3)];

			if (Current != UNASSIGNED && Nums[Current] == true)
			{
				m_GridStatus = false;

				return;
			}

			Nums[Current] = true;
		}
	}

	for (int i = 0; i < 9; i++)
	{
		m_Numbers[i] = i + 1;
	}

	std::random_shuffle(std::begin(m_Numbers), std::end(m_Numbers), Random);

	m_GridStatus = true;
}

bool Sudoku::VerifyGridStatus()
{
	return m_GridStatus;
}

void Sudoku::PrintGrid()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (m_Grid[i][j] == 0)
				std::cout << ".";
			else
				std::cout << m_Grid[i][j];
			std::cout << "|";
		}
		std::cout << std::endl;
	}

	std::cout << "\nDifficulty of current sudoku(0 being easiest): " << m_DifficultyLevel;
	std::cout << std::endl;
}

bool Sudoku::SolveGrid()
{
	int Row, Col;
	
	if (!FindUnassignedLocation(m_Grid, Row, Col))
	{
		return true;
	}

	for (int Num = 0; Num < 9; Num++)
	{
		if (IsSafe(m_Grid, Row, Col, m_Numbers[Num]))
		{
			m_Grid[Row][Col] = m_Numbers[Num];

			if (SolveGrid())
			{
				return true;
			}

			m_Grid[Row][Col] = UNASSIGNED;
		}
	}

	return false;

}

void Sudoku::CountSolutions(int& Number)
{
	int Row, Col;

	if (!FindUnassignedLocation(m_Grid, Row, Col))
	{
		Number++;

		return;
	}


	for (int i = 0; i < 9 && Number < 2; i++)
	{
		if (IsSafe(m_Grid, Row, Col, m_Numbers[i]))
		{
			m_Grid[Row][Col] = m_Numbers[i];

			CountSolutions(Number);
		}

		m_Grid[Row][Col] = UNASSIGNED;
	}

}

void Sudoku::GeneratePuzzle()
{
	for (int i = 0; i < 81; i++)
	{
		int x = (m_GridPosition[i]) / 9;
		int y = (m_GridPosition[i]) % 9;
		int Temp = m_Grid[x][y];

		m_Grid[x][y] = UNASSIGNED;

		int Check = 0;

		CountSolutions(Check);

		if (Check != 1)
		{
			m_Grid[x][y] = Temp;
		}
	}
}

int Sudoku::BranchDifficultyScore()
{
	int EmptyPositions = -1;
	int Sum = 0;

	std::array<std::array<int, 9>, 9> TempGrid;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			TempGrid[i][j] = m_Grid[i][j];
		}
	}

	while (EmptyPositions != 0)
	{
		std::vector<std::vector<int>> Empty;

		for (int i = 0; i < 81; i++)
		{
			if (TempGrid[static_cast<int>(i / 9)][static_cast<int>(i % 9)] == 0)
			{
				std::vector<int> Temp;

				Temp.push_back(i);

				for (int Num = 1; Num <= 9; Num++)
				{
					if (IsSafe(TempGrid, i / 9, i % 9, Num))
					{
						Temp.push_back(Num);
					}
				}

				Empty.push_back(Temp);
			}

		}

		if (Empty.size() == 0)
		{
			std::cout << "Hello: " << Sum << std::endl;

			return Sum;
		}

		int MinIndex = 0;
		int Check = Empty.size();

		for (int i = 0; i < Check; i++)
		{
			if (Empty[i].size() < Empty[MinIndex].size())
			{
				MinIndex = i;
			}
		}

		int BranchFactor = Empty[MinIndex].size();
		int RowIndex = Empty[MinIndex][0] / 9;
		int ColIndex = Empty[MinIndex][0] % 9;

		TempGrid[RowIndex][ColIndex] = m_SolutionGrid[RowIndex][ColIndex];
		Sum += ((BranchFactor - 2) * (BranchFactor - 2));

		EmptyPositions = Empty.size() - 1;
	}

	return Sum;

}

void Sudoku::CalculateDifficulty()
{
	int B = BranchDifficultyScore();
	int EmptyCells = 0;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (m_Grid[i][j] == 0)
			{
				EmptyCells++;
			}
		}
	}

	m_DifficultyLevel = B * 100 + EmptyCells;
}

const std::array<std::array<int, 9>, 9>& Sudoku::GetGrid() const
{
	return m_Grid;
}

const std::array<std::array<int, 9>, 9>& Sudoku::GetSolutionGrid() const
{
	return m_SolutionGrid;
}
