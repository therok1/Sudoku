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
	ConstructEndMenuUI();
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

		m_GameElements["Stats"]->SetText(std::format("{:%T} - {} / 3 {}", std::chrono::round<std::chrono::seconds>(std::chrono::duration<int>{ GetGameTime().count() }), m_Mistakes, m_Mistakes == 1 ? "Mistake" : "Mistakes"));
		
		m_GameElements["Selected"]->SetText(m_Selected ? std::to_string(m_Selected) : "CLR");
		m_GameElements["Selected"]->SetFitText();
		m_GameElements["Selected"]->SetX(Mouse.MouseCoords.x - m_GameElements["Selected"]->GetRect().w - 10);
		m_GameElements["Selected"]->SetY(Mouse.MouseCoords.y);
	}
	else if (m_State == InEndMenu)
	{
		UpdateEndMenuUI();
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
					InitSudoku();

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

				if (m_EndMenuElements["Start"]->MouseRelease(m_State, InEndMenu))
				{
					InitSudoku();

					break;
				}

				if (m_EndMenuElements["Menu"]->MouseRelease(m_State, InEndMenu))
				{
					m_State = InMenu;

					break;
				}

				if (m_EndMenuElements["Quit"]->MouseRelease(m_State, InEndMenu))
				{
					m_Running = false;

					break;
				}

				m_Grid->FillCell(m_State, InGame, m_Selected, m_Mistakes);
				m_SidePanel->Select(m_State, InGame, m_Selected);

				if (m_State == InGame)
				{
					if (m_Mistakes > 3)
					{
						m_State = InEndMenu;

						m_EndMenuElements["Title"]->SetText("Game Over");
						m_EndMenuElements["Message"]->SetText("You have made 3 mistakes and lost this game");
						m_EndMenuElements["Stats"]->SetText(std::format("{:%T}", std::chrono::round<std::chrono::seconds>(std::chrono::duration<int>{ GetGameTime().count() })));

						break;
					}
					else if (m_Grid->GetSudoku() == m_Sudoku->GetSolutionGrid())
					{
						m_State = InEndMenu;

						m_EndMenuElements["Title"]->SetText("Congratulations");
						m_EndMenuElements["Message"]->SetText("You have completed sudoku");
						m_EndMenuElements["Stats"]->SetText(std::format("{:%T}", std::chrono::round<std::chrono::seconds>(std::chrono::duration<int>{ GetGameTime().count() })));

						break;
					}
				}
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
	else if (m_State == InEndMenu)
	{
		RenderEndMenuUI();
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
	m_MenuElements["Credits"]->SetFontSize(25);
	m_MenuElements["Credits"]->SetFont("Assets/Fonts/UniSansThin.ttf");
	m_MenuElements["Credits"]->SetFocusable(false);

	m_MenuElements.emplace("Start", std::make_unique<Button>(200, 50, 0, 0, 0.5f, 0.5f, 0.5f, 0.5f));
	m_MenuElements["Start"]->SetColour(SDL_Color(140, 188, 255, 255));
	m_MenuElements["Start"]->SetText("Start");
	m_MenuElements["Start"]->SetFontSize(20);
	m_MenuElements["Start"]->SetTextColour(SDL_Color(255, 255, 255, 255));

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
}

void Game::ConstructEndMenuUI()
{
	m_EndMenuElements.emplace("Title", std::make_unique<Button>(400, 100, 0, 150, 0.5f, 0.0f, 0.5f, 0.0f));
	m_EndMenuElements["Title"]->SetColour(SDL_Color(0, 0, 0, 0));
	m_EndMenuElements["Title"]->SetText("Game Over");
	m_EndMenuElements["Title"]->SetFontSize(100);
	m_EndMenuElements["Title"]->SetFocusable(false);

	m_EndMenuElements.emplace("Message", std::make_unique<Button>(400, 100, 0, 200, 0.5f, 0.0f, 0.5f, 0.0f));
	m_EndMenuElements["Message"]->SetColour(SDL_Color(0, 0, 0, 0));
	m_EndMenuElements["Message"]->SetText("Message");
	m_EndMenuElements["Message"]->SetFontSize(25);
	m_EndMenuElements["Message"]->SetFocusable(false);
	
	m_EndMenuElements.emplace("Stats", std::make_unique<Button>(400, 100, 0, 230, 0.5f, 0.0f, 0.5f, 0.0f));
	m_EndMenuElements["Stats"]->SetColour(SDL_Color(0, 0, 0, 0));
	m_EndMenuElements["Stats"]->SetText("Message");
	m_EndMenuElements["Stats"]->SetFontSize(20);
	m_EndMenuElements["Stats"]->SetFont("Assets/Fonts/UniSansThin.ttf");
	m_EndMenuElements["Stats"]->SetFocusable(false);

	m_EndMenuElements.emplace("Start", std::make_unique<Button>(200, 50, 0, 0, 0.5f, 0.5f, 0.5f, 0.5f));
	m_EndMenuElements["Start"]->SetColour(SDL_Color(140, 188, 255, 255));
	m_EndMenuElements["Start"]->SetText("New Game");
	m_EndMenuElements["Start"]->SetFontSize(20);
	m_EndMenuElements["Start"]->SetTextColour(SDL_Color(255, 255, 255, 255));

	m_EndMenuElements.emplace("Menu", std::make_unique<Button>(200, 50, 0, 0, 0.5f, 0.5f, 0.5f, 0.6f));
	m_EndMenuElements["Menu"]->SetColour(SDL_Color(230, 230, 230, 255));
	m_EndMenuElements["Menu"]->SetText("Home");
	m_EndMenuElements["Menu"]->SetFontSize(20);
	m_EndMenuElements["Menu"]->SetTextColour(SDL_Color(0, 0, 0, 255));

	m_EndMenuElements.emplace("Quit", std::make_unique<Button>(200, 50, 0, 0, 0.5f, 0.5f, 0.5f, 0.7f));
	m_EndMenuElements["Quit"]->SetColour(SDL_Color(230, 230, 230, 255));
	m_EndMenuElements["Quit"]->SetText("Quit");
	m_EndMenuElements["Quit"]->SetFontSize(20);
	m_EndMenuElements["Quit"]->SetTextColour(SDL_Color(0, 0, 0, 255));
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

void Game::RenderEndMenuUI()
{
	for (const auto& Button : m_EndMenuElements)
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

void Game::UpdateEndMenuUI()
{
	for (const auto& Button : m_EndMenuElements)
	{
		Button.second->Update();
	}
}

void Game::InitSudoku()
{
	m_Sudoku.reset();

	m_Mistakes = 0;
	m_Selected = 0;

	m_Sudoku = std::make_unique<Sudoku>();
	m_Sudoku->CreateSeed();
	m_Sudoku->GeneratePuzzle();
	m_Sudoku->CalculateDifficulty();

	m_Grid->FillBoard(m_Sudoku->GetGrid(), m_Sudoku->GetSolutionGrid());

	m_State = InGame;

	m_GameStart = std::chrono::steady_clock::now();
}

bool Game::GetRunning() const
{
	return m_Running;
}

std::chrono::seconds Game::GetGameTime() const
{
	std::chrono::steady_clock::duration TimeElapsed = std::chrono::steady_clock::now() - m_GameStart;
	std::chrono::seconds Seconds = std::chrono::duration_cast<std::chrono::seconds>(TimeElapsed);

	return Seconds;
}
 