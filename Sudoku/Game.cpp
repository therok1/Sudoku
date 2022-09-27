#include "Game.h"

void Lerp(SDL_Color* Out, SDL_Color Start, SDL_Color End, float Factor)
{
	float Temp = 1.0f - Factor;

	Out->r = static_cast<float>(Start.r) * Temp + static_cast<float>(End.r) * Factor;
	Out->g = static_cast<float>(Start.g) * Temp + static_cast<float>(End.g) * Factor;
	Out->b = static_cast<float>(Start.b) * Temp + static_cast<float>(End.b) * Factor;
}

Game::Game()
{
	SDL_Color PrimaryColor = { 215, 242, 250, 255 };
	SDL_Color SecondaryColor = { 197, 228, 237, 255 };
	SDL_Color BackgroundLight = { 255, 255, 255, 255 };
	SDL_Color BackgroundDark = { 54, 57, 63, 255 };
	SDL_Color ButtonsLight = { 230, 230, 230, 255 };
	SDL_Color ButtonsDark = { 47, 49, 54, 255 };

	m_Running = true;
	m_State = InMenu;

	m_Start = std::make_unique<Button>(200, 50, 0, 0, 0.5f, 0.5f, 0.5f, 0.5f);
	m_Start->SetColour(ButtonsLight);
	m_Start->SetText("Start");

	m_Settings = std::make_unique<Button>(200, 50, 0, 0, 0.5f, 0.5f, 0.5f, 0.6f);
	m_Settings->SetColour(ButtonsLight);
	m_Settings->SetText("Settings");

	m_Quit = std::make_unique<Button>(200, 50, 0, 0, 0.5f, 0.5f, 0.5f, 0.7f);
	m_Quit->SetColour(ButtonsLight);
	m_Quit->SetText("Quit");

	m_Buttons.emplace("Start", std::move(m_Start));
	m_Buttons.emplace("Settings", std::move(m_Settings));
	m_Buttons.emplace("Quit", std::move(m_Quit));

	/*Sudoku Sudoku;
	Sudoku.CreateSeed();
	Sudoku.GeneratePuzzle();
	Sudoku.CalculateDifficulty();
	Sudoku.PrintGrid();*/

	m_Text = std::make_unique<DynamicText>(0, 0, "8", 16, "Assets/Fonts/UniSans.ttf");

	m_Grid = std::make_unique<Board>(81, PrimaryColor, SecondaryColor);
	m_Grid->GenerateBoard();
	m_Grid->SetX(0, true, 0.5);
	m_Grid->SetY(0, true, 0.5);
	m_Grid->SetAnchorPoint(0.5f, 0.5f);

	BackgroundAnim = std::make_unique<Animation>(1000, BackgroundLight, BackgroundDark);
	ButtonsAnim = std::make_unique<Animation>(1000, ButtonsLight, ButtonsDark);
}

Game::~Game()
{

}

void Game::Tick()
{
	BackgroundAnim->CurrentTime = SDL_GetTicks();

	if (BackgroundAnim->Active)
	{
		if (BackgroundAnim->CurrentTime > BackgroundAnim->StartTime + BackgroundAnim->Duration)
		{
			BackgroundAnim->Active = false;
			Settings.DarkMode = !Settings.DarkMode;
		}
		else
		{
			float Factor = (static_cast<float>(BackgroundAnim->CurrentTime - BackgroundAnim->StartTime) / BackgroundAnim->Duration);

			if (!Settings.DarkMode)
			{
				Lerp(&BackgroundAnim->Result, BackgroundAnim->Start, BackgroundAnim->End, Factor);
			}
			else
			{
				Lerp(&BackgroundAnim->Result, BackgroundAnim->End, BackgroundAnim->Start, Factor);
			}
		}
	}

	ButtonsAnim->CurrentTime = SDL_GetTicks();

	if (ButtonsAnim->Active)
	{
		if (ButtonsAnim->CurrentTime > ButtonsAnim->StartTime + ButtonsAnim->Duration)
		{
			ButtonsAnim->Active = false;
		}
		else
		{
			float Factor = (static_cast<float>(ButtonsAnim->CurrentTime - ButtonsAnim->StartTime) / ButtonsAnim->Duration);

			if (!Settings.DarkMode)
			{
				Lerp(&ButtonsAnim->Result, ButtonsAnim->Start, ButtonsAnim->End, Factor);
			}
			else
			{
				Lerp(&ButtonsAnim->Result, ButtonsAnim->End, ButtonsAnim->Start, Factor);
			}
		}
	}

	for (const auto& Button : m_Buttons)
	{
		Button.second->Update();
	}

	m_Grid->Update();
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
		case SDL_MOUSEBUTTONUP:
			if (Event.button.button == SDL_BUTTON_LEFT)
			{
				if (m_Buttons["Start"]->MouseRelease(m_State, InMenu))
				{
					m_State = InGame;
				}

				if (m_Buttons["Settings"]->MouseRelease(m_State, InMenu))
				{
					BackgroundAnim->Active = true;
					BackgroundAnim->StartTime = BackgroundAnim->CurrentTime;

					ButtonsAnim->Active = true;
					ButtonsAnim->StartTime = ButtonsAnim->CurrentTime;

				}

				if (m_Buttons["Quit"]->MouseRelease(m_State, InMenu))
				{
					m_Running = false;
				}
			}
		default:
			break; 
		}
	}
}

void Game::Render()
{
	m_Buttons["Start"]->SetColour(ButtonsAnim->Result);
	m_Buttons["Settings"]->SetColour(ButtonsAnim->Result);
	m_Buttons["Quit"]->SetColour(ButtonsAnim->Result);

	SDL_SetRenderDrawColor(Window.Renderer, BackgroundAnim->Result.r, BackgroundAnim->Result.g, BackgroundAnim->Result.b, 255);

	SDL_RenderClear(Window.Renderer);

	if (m_State == InMenu)
	{
		for (const auto& Button : m_Buttons)
		{
			Button.second->Render();
		}
	}
	else if (m_State == InGame)
	{
		m_Grid->Render();
	}

	m_Text->Render();

	SDL_RenderPresent(Window.Renderer);
}

bool Game::GetRunning() const
{
	return m_Running;
}
 