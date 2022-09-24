#pragma once


#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <random>

#define UNASSIGNED 0

class Sudoku 
{
public:

	Sudoku();
	Sudoku(const std::string& GridString, bool RowMajor = true);

	void FillEmptyDiagonalBox(int Index);
	void CreateSeed();
	void PrintGrid();
	void CountSolutions(int& Number);
	void GeneratePuzzle();
	void CalculateDifficulty();

	int BranchDifficultyScore();

	bool SolveGrid();
	bool VerifyGridStatus();

	std::string GetGrid();

private:

	std::array<std::array<int, 9>, 9> m_Grid;
	std::array<std::array<int, 9>, 9> m_SolutionGrid;
	std::array<int, 9> m_Numbers;
	std::array<int, 81> m_GridPosition;

	int m_DifficultyLevel;

	bool m_GridStatus;

};
