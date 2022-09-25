#include "Game.h"

Uint32 Game::m_MouseButtons = Uint32();
SDL_Point Game::m_MouseCoords = SDL_Point();

Game::Game()
{
	m_Running = true;

	m_State = InMenu;

	Start = std::make_unique<Button>(200, 50, 0, 0, 0.5f, 0.5f, 0.5f, 0.5f);
	Start->SetColour({ 255, 255, 255, 255 });

	Settings = std::make_unique<Button>(200, 50, 0, 0, 0.5f, 0.5f, 0.5f, 0.6f);
	Settings->SetColour({ 255, 255, 255, 255 });

	Quit = std::make_unique<Button>(200, 50, 0, 0, 0.5f, 0.5f, 0.5f, 0.7f);
	Quit->SetColour({ 255, 255, 255, 255 });

	m_Buttons.emplace("Start", std::move(Start));
	m_Buttons.emplace("Settings", std::move(Settings));
	m_Buttons.emplace("Quit", std::move(Quit));

	Sudoku Sudoku;
	Sudoku.CreateSeed();
	Sudoku.GeneratePuzzle();
	Sudoku.CalculateDifficulty();
	Sudoku.PrintGrid();

	Text = std::make_unique<DynamicText>(0, 0, "8", 32, "Assets/Fonts/CascadiaCode.ttf");

	SDL_Color PrimaryColor = { 215, 242, 250, 255 };
	SDL_Color SecondaryColor = { 197, 228, 237, 255 };

	Grid = std::make_unique<Board>(81, PrimaryColor, SecondaryColor);
	Grid->GenerateBoard();
	Grid->SetX(0, true, 0.5);
	Grid->SetY(0, true, 0.5);
	Grid->SetAnchorPoint(0.5f, 0.5f);
}

Game::~Game()
{

}

void Game::Tick()
{
	for (const auto& Button : m_Buttons)
	{
		Button.second->Update();
	}

	Grid->Update();
}

void Game::EventLoop()
{
	SDL_Event Event;

	while (m_Running && SDL_PollEvent(&Event))
	{
		m_MouseButtons = SDL_GetMouseState(&m_MouseCoords.x, &m_MouseCoords.y);

		switch (Event.type)
		{
		case SDL_QUIT: 
			m_Running = false;

			break;
		case SDL_MOUSEBUTTONUP:
			if (Event.button.button == SDL_BUTTON_LEFT)
			{
				if (m_Buttons["Quit"]->GetFocusable())
				{
					if (m_Buttons["Quit"]->MouseRelease(m_State, InMenu))
					{
						m_Running = false;
					}
				}
			}
		default:
			break; 
		}
	}
}

void Game::Render()
{
	SDL_RenderClear(Window::m_Renderer);

	Grid->Render();
	Text->Render();

	for (const auto& Button : m_Buttons)
	{
		Button.second->Render();
	}

	SDL_RenderPresent(Window::m_Renderer);
}

bool Game::GetRunning() const
{
	return m_Running;
}
 