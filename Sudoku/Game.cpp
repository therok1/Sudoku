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

	SDL_Color TextLight = { 0, 0, 0, 255 };
	SDL_Color TextDark = { 255, 255, 255, 255 };

	m_Selected = 1;
	m_Running = true;
	m_State = InMenu;

	m_Title = std::make_unique<Button>(400, 100, 0, 150, 0.5f, 0.0f, 0.5f, 0.0f);
	m_Title->SetColour({ 0, 0, 0, 0 });
	m_Title->SetText("Sudoku");
	m_Title->SetFontSize(100);
	m_Title->SetFocusable(false);

	m_Credits = std::make_unique<Button>(400, 100, 0, 200, 0.5f, 0.0f, 0.5f, 0.0f);
	m_Credits->SetColour({ 0, 0, 0, 0 });
	m_Credits->SetText("By @therok1");
	m_Credits->SetFontSize(30);
	m_Credits->SetFont("Assets/Fonts/UniSansThin.ttf");
	m_Credits->SetFocusable(false);

	m_Start = std::make_unique<Button>(200, 50, 0, 0, 0.5f, 0.5f, 0.5f, 0.5f);
	m_Start->SetColour(ButtonsLight);
	m_Start->SetText("Start");
	m_Start->SetFontSize(20);
	m_Start->SetTextColour({ 0, 0, 0, 255 });

	m_Settings = std::make_unique<Button>(200, 50, 0, 0, 0.5f, 0.5f, 0.5f, 0.6f);
	m_Settings->SetColour(ButtonsLight);
	m_Settings->SetText("Settings");
	m_Settings->SetFontSize(20);
	m_Settings->SetTextColour({ 0, 0, 0, 255 });

	m_Quit = std::make_unique<Button>(200, 50, 0, 0, 0.5f, 0.5f, 0.5f, 0.7f);
	m_Quit->SetColour(ButtonsLight);
	m_Quit->SetText("Quit");
	m_Quit->SetFontSize(20);
	m_Quit->SetTextColour({ 0, 0, 0, 255 });

	m_Buttons.emplace("Title", std::move(m_Title));
	m_Buttons.emplace("Credits", std::move(m_Credits));
	m_Buttons.emplace("Start", std::move(m_Start));
	m_Buttons.emplace("Settings", std::move(m_Settings));
	m_Buttons.emplace("Quit", std::move(m_Quit));

	m_Grid = std::make_unique<Board>(81, PrimaryColor, SecondaryColor);
	m_Grid->GenerateBoard();
	m_Grid->SetX(0, true, 0.5f);
	m_Grid->SetY(0, true, 0.5f);
	m_Grid->SetAnchorPoint(0.5f, 0.5f);

	m_SidePanel = std::make_unique<SidePanel>();
	m_SidePanel->GeneratePanel();
	m_SidePanel->SetX(0, true, 1.0f);
	m_SidePanel->SetAnchorPoint(1.0f, 0.0f);

	m_Sudoku = std::make_unique<Sudoku>();

	BackgroundAnim = std::make_unique<Animation>(1000, BackgroundLight, BackgroundDark);
	ButtonsAnim = std::make_unique<Animation>(1000, ButtonsLight, ButtonsDark);
	TextAnim = std::make_unique<Animation>(1000, TextLight, TextDark);
}

Game::~Game()
{

}

void Game::Tick()
{
	ThemeUpdate();

	if (m_State == InMenu)
	{
		for (const auto& Button : m_Buttons)
		{
			Button.second->Update();
		}
	}
	else if (m_State == InGame)
	{
		m_Grid->Update();
		m_SidePanel->Update();
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
		case SDL_MOUSEBUTTONUP:
			if (Event.button.button == SDL_BUTTON_LEFT)
			{
				m_Grid->FillCell(m_State, InGame, m_Selected);

				if (m_Buttons["Start"]->MouseRelease(m_State, InMenu))
				{
					m_Sudoku->CreateSeed();
					m_Sudoku->GeneratePuzzle();
					m_Sudoku->CalculateDifficulty();
					m_Sudoku->PrintGrid();

					std::array<std::array<int, 9>, 9> Puzzle = m_Sudoku->GetGrid();
					std::array<std::array<int, 9>, 9> PuzzleSolution = m_Sudoku->GetSolutionGrid();
					
					m_Grid->FillBoard(Puzzle, PuzzleSolution);

					m_State = InGame;
				}

				if (m_Buttons["Settings"]->MouseRelease(m_State, InMenu))
				{
					ThemeActivate();
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

	m_Buttons["Title"]->SetTextColour(TextAnim->Result);
	m_Buttons["Credits"]->SetTextColour(TextAnim->Result);
	m_Buttons["Start"]->SetTextColour(TextAnim->Result);
	m_Buttons["Settings"]->SetTextColour(TextAnim->Result);
	m_Buttons["Quit"]->SetTextColour(TextAnim->Result);

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
		m_SidePanel->Render();
	}

	SDL_RenderPresent(Window.Renderer);
}

void Game::ThemeUpdate()
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


	TextAnim->CurrentTime = SDL_GetTicks();

	if (TextAnim->Active)
	{
		if (TextAnim->CurrentTime > TextAnim->StartTime + TextAnim->Duration)
		{
			TextAnim->Active = false;
		}
		else
		{
			float Factor = (static_cast<float>(TextAnim->CurrentTime - TextAnim->StartTime) / TextAnim->Duration);

			if (!Settings.DarkMode)
			{
				Lerp(&TextAnim->Result, TextAnim->Start, TextAnim->End, Factor);
			}
			else
			{
				Lerp(&TextAnim->Result, TextAnim->End, TextAnim->Start, Factor);
			}
		}
	}
}

void Game::ThemeActivate()
{
	BackgroundAnim->Active = true;
	BackgroundAnim->StartTime = BackgroundAnim->CurrentTime;

	ButtonsAnim->Active = true;
	ButtonsAnim->StartTime = ButtonsAnim->CurrentTime;

	TextAnim->Active = true;
	TextAnim->StartTime = TextAnim->CurrentTime;
}

bool Game::GetRunning() const
{
	return m_Running;
}
 