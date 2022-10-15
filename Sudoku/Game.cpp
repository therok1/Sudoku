#include "Game.h"

Game::Game()
{
	m_Mistakes = 0;
	m_Selected = 0;

	m_Running = true;

	m_State = InMenu;

	m_GameStart = std::chrono::steady_clock::now();

	ConstructMenuUI();
	ConstructGameUI();
}

Game::~Game()
{
	
}

void Game::Tick()
{
	if (m_State == InMenu)
	{
		UpdateMenuUI();
	}
	else if (m_State == InGame)
	{
		UpdateGameUI();

		std::chrono::steady_clock::duration TimeElapsed = std::chrono::steady_clock::now() - m_GameStart;
		std::chrono::seconds Seconds = std::chrono::duration_cast<std::chrono::seconds>(TimeElapsed);

		m_GameElements["Stats"]->SetText(std::format("{:%T} - {} / 3 {}", std::chrono::round<std::chrono::seconds>(std::chrono::duration<int>{ Seconds.count() }), m_Mistakes, m_Mistakes == 1 ? "Mistake" : "Mistakes"));
		
		m_GameElements["Selected"]->SetText(m_Selected ? std::to_string(m_Selected) : "CLR");
		m_GameElements["Selected"]->SetFitText();
		m_GameElements["Selected"]->SetX(Mouse.MouseCoords.x - m_GameElements["Selected"]->GetRect().w - 10);
		m_GameElements["Selected"]->SetY(Mouse.MouseCoords.y);
	}
}

void Game::EventLoop()
{
	SDL_Event Event;

	while (m_Running && SDL_PollEvent(&Event))
	{
		Mouse.MouseButtons = SDL_GetMouseState(&Mouse.MouseCoords.x, &Mouse.MouseCoords.y);

		switch (Event.type)
		{
		case SDL_QUIT: 
			m_Running = false;

			break;
		case SDL_WINDOWEVENT:
			switch (Event.window.event)
			{
			case SDL_WINDOWEVENT_LEAVE:
				m_GameElements["Selected"]->SetTextAlpha(0);

				break;
			case SDL_WINDOWEVENT_ENTER:
				m_GameElements["Selected"]->SetTextAlpha(255);

				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (Event.button.button == SDL_BUTTON_LEFT)
			{
				if (m_MenuElements["Start"]->MouseRelease(m_State, InMenu))
				{
					m_Sudoku->CreateSeed();
					m_Sudoku->GeneratePuzzle();
					m_Sudoku->CalculateDifficulty();
					
					std::array<std::array<int, 9>, 9> Puzzle = m_Sudoku->GetGrid();
					std::array<std::array<int, 9>, 9> PuzzleSolution = m_Sudoku->GetSolutionGrid();
					
					m_Grid->FillBoard(Puzzle, PuzzleSolution);

					m_State = InGame;

					m_GameStart = std::chrono::steady_clock::now();

					break;
				}

				if (m_MenuElements["Settings"]->MouseRelease(m_State, InMenu))
				{
					break;
				}

				if (m_MenuElements["Quit"]->MouseRelease(m_State, InMenu))
				{
					m_Running = false;

					break;
				}

				m_Grid->FillCell(m_State, InGame, m_Selected, m_Mistakes);
				m_SidePanel->Select(m_State, InGame, m_Selected);
			}
			else if (Event.button.button == SDL_BUTTON_RIGHT)
			{
				m_Selected = 0;
			}

			break;
		default:
			break; 
		}
	}
}

void Game::Render()
{
	SDL_SetRenderDrawColor(Window.Renderer, 255, 255, 255, 255);

	SDL_RenderClear(Window.Renderer);

	if (m_State == InMenu)
	{
		RenderMenuUI();
	}
	else if (m_State == InGame)
	{
		RenderGameUI();
	}

	SDL_RenderPresent(Window.Renderer);
}

void Game::ConstructMenuUI()
{
	m_MenuElements.emplace("Title", std::make_unique<Button>(400, 100, 0, 150, 0.5f, 0.0f, 0.5f, 0.0f));
	m_MenuElements["Title"]->SetColour(SDL_Color(0, 0, 0, 0));
	m_MenuElements["Title"]->SetText("Sudoku");
	m_MenuElements["Title"]->SetFontSize(100);
	m_MenuElements["Title"]->SetFocusable(false);

	m_MenuElements.emplace("Credits", std::make_unique<Button>(400, 100, 0, 200, 0.5f, 0.0f, 0.5f, 0.0f));
	m_MenuElements["Credits"]->SetColour(SDL_Color(0, 0, 0, 0));
	m_MenuElements["Credits"]->SetText("By @therok1");
	m_MenuElements["Credits"]->SetFontSize(30);
	m_MenuElements["Credits"]->SetFont("Assets/Fonts/UniSansThin.ttf");
	m_MenuElements["Credits"]->SetFocusable(false);

	m_MenuElements.emplace("Start", std::make_unique<Button>(200, 50, 0, 0, 0.5f, 0.5f, 0.5f, 0.5f));
	m_MenuElements["Start"]->SetColour(SDL_Color(230, 230, 230, 255));
	m_MenuElements["Start"]->SetText("Start");
	m_MenuElements["Start"]->SetFontSize(20);
	m_MenuElements["Start"]->SetTextColour(SDL_Color(0, 0, 0, 255));

	m_MenuElements.emplace("Settings", std::make_unique<Button>(200, 50, 0, 0, 0.5f, 0.5f, 0.5f, 0.6f));
	m_MenuElements["Settings"]->SetColour(SDL_Color(230, 230, 230, 255));
	m_MenuElements["Settings"]->SetText("Settings");
	m_MenuElements["Settings"]->SetFontSize(20);
	m_MenuElements["Settings"]->SetTextColour(SDL_Color(0, 0, 0, 255));

	m_MenuElements.emplace("Quit", std::make_unique<Button>(200, 50, 0, 0, 0.5f, 0.5f, 0.5f, 0.7f));
	m_MenuElements["Quit"]->SetColour(SDL_Color(230, 230, 230, 255));
	m_MenuElements["Quit"]->SetText("Quit");
	m_MenuElements["Quit"]->SetFontSize(20);
	m_MenuElements["Quit"]->SetTextColour(SDL_Color(0, 0, 0, 255));
}

void Game::ConstructGameUI()
{
	m_GameElements.emplace("Title", std::make_unique<Button>(400, 100, 0, 30, 0.5f, 0.0f, 0.5f, 0.0f));
	m_GameElements["Title"]->SetColour(SDL_Color(0, 0, 0, 0));
	m_GameElements["Title"]->SetText("Sudoku");
	m_GameElements["Title"]->SetFontSize(50);
	m_GameElements["Title"]->SetFocusable(false);
	
	m_GameElements.emplace("Stats", std::make_unique<Button>(400, 100, 0, 60, 0.5f, 0.0f, 0.5f, 0.0f));
	m_GameElements["Stats"]->SetColour(SDL_Color(0, 0, 0, 0));
	m_GameElements["Stats"]->SetText("00:00 - 0 Mistakes");
	m_GameElements["Stats"]->SetFontSize(15);
	m_GameElements["Stats"]->SetFont("Assets/Fonts/UniSansThin.ttf");
	m_GameElements["Stats"]->SetFocusable(false);

	m_GameElements.emplace("Selected", std::make_unique<Button>(30, 30, 0, 0, 0.5f, 0.5f, 0.5f, 0.7f));
	m_GameElements["Selected"]->SetColour(SDL_Color(0, 0, 0, 0));
	m_GameElements["Selected"]->SetText("CLR");
	m_GameElements["Selected"]->SetFontSize(20);
	m_GameElements["Selected"]->SetTextColour(SDL_Color(0, 0, 0, 255));
	m_GameElements["Selected"]->SetFocusable(false);
	
	m_Grid = std::make_unique<Board>(81, SDL_Color(230, 230, 230, 255), SDL_Color(220, 220, 220, 255));
	m_Grid->GenerateBoard();
	m_Grid->SetX(0, true, 0.5f);
	m_Grid->SetY(0, true, 0.5f);
	m_Grid->SetAnchorPoint(0.5f, 0.5f);
	
	m_SidePanel = std::make_unique<SidePanel>();
	m_SidePanel->GeneratePanel();
	m_SidePanel->SetX(0, true, 0.5f);
	m_SidePanel->SetY(0, true, 0.9f);
	m_SidePanel->SetAnchorPoint(0.5f, 1.0f);

	m_Sudoku = std::make_unique<Sudoku>();
}

void Game::RenderMenuUI()
{
	for (const auto& Button : m_MenuElements)
	{
		Button.second->Render();
	}
}

void Game::RenderGameUI()
{
	m_Grid->Render();
	m_SidePanel->Render();

	for (const auto& Button : m_GameElements)
	{
		Button.second->Render();
	}
}

void Game::UpdateMenuUI()
{
	for (const auto& Button : m_MenuElements)
	{
		Button.second->Update();
	}
}

void Game::UpdateGameUI()
{
	m_Grid->Update();
	m_SidePanel->Update();

	for (const auto& Button : m_GameElements)
	{
		Button.second->Update();
	}
}

bool Game::GetRunning() const
{
	return m_Running;
}
 