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
	SDL_Color PrimaryColor = { 230, 230, 230, 255 }; // 215 242 250
	SDL_Color SecondaryColor = { 220, 220, 220, 255 }; // 197 228 237

	SDL_Color BackgroundLight = { 255, 255, 255, 255 };
	SDL_Color BackgroundDark = { 54, 57, 63, 255 };
	SDL_Color ButtonsLight = { 230, 230, 230, 255 };
	SDL_Color ButtonsDark = { 47, 49, 54, 255 };

	SDL_Color TextLight = { 0, 0, 0, 255 };
	SDL_Color TextDark = { 255, 255, 255, 255 };

	m_Mistakes = 0;
	m_Selected = 0;
	m_Running = true;
	m_State = InMenu;
	m_GameStart = std::chrono::steady_clock::now();

	m_Title = std::make_unique<Button>(400, 100, 0, 150, 0.5f, 0.0f, 0.5f, 0.0f);
	m_Title->SetColour({ 0, 0, 0, 0 });
	m_Title->SetText("Sudoku");
	m_Title->SetFontSize(100);
	m_Title->SetFocusable(false);

	m_Title1 = std::make_unique<Button>(400, 100, 0, 30, 0.5f, 0.0f, 0.5f, 0.0f);
	m_Title1->SetColour({ 0, 0, 0, 0 });
	m_Title1->SetText("Sudoku");
	m_Title1->SetFontSize(50);
	m_Title1->SetFocusable(false);

	m_Timer = std::make_unique<Button>(400, 100, 0, 60, 0.5f, 0.0f, 0.5f, 0.0f);
	m_Timer->SetColour({ 0, 0, 0, 0 });
	m_Timer->SetText("00:00 - 0 Mistakes");
	m_Timer->SetFontSize(15);
	m_Timer->SetFont("Assets/Fonts/UniSansThin.ttf");
	m_Timer->SetFocusable(false);

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

	m_MouseIcon = std::make_unique<Button>(30, 30, 0, 0, 0.5f, 0.5f, 0.5f, 0.7f);
	m_MouseIcon->SetColour({ 255, 0, 0, 0 });
	m_MouseIcon->SetText("0");
	m_MouseIcon->SetFontSize(20);
	m_MouseIcon->SetTextColour({ 0, 0, 0, 255 });

	m_MenuButtons.emplace("Title", std::move(m_Title));
	m_MenuButtons.emplace("Credits", std::move(m_Credits));
	m_MenuButtons.emplace("Start", std::move(m_Start));
	m_MenuButtons.emplace("Settings", std::move(m_Settings));
	m_MenuButtons.emplace("Quit", std::move(m_Quit));

	m_Grid = std::make_unique<Board>(81, PrimaryColor, SecondaryColor);
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
		for (const auto& Button : m_MenuButtons)
		{
			Button.second->Update();
		}
	}
	else if (m_State == InGame)
	{
		std::chrono::steady_clock::duration TimeElapsed = std::chrono::steady_clock::now() - m_GameStart;
		std::chrono::seconds Seconds = std::chrono::duration_cast<std::chrono::seconds>(TimeElapsed);
		
		m_Grid->Update();
		m_SidePanel->Update();

		m_Timer->SetText(std::format("{:%T} - {} {}", std::chrono::round<std::chrono::seconds>(std::chrono::duration<int>{ Seconds.count() }), m_Mistakes, m_Mistakes == 1 ? "Mistake" : "Mistakes"));

		m_MouseIcon->SetText(m_Selected ? std::to_string(m_Selected) : "CLR");
		m_MouseIcon->SetFitText();
		m_MouseIcon->SetX(Mouse.MouseCoords.x - m_MouseIcon->GetRect().w - 10);
		m_MouseIcon->SetY(Mouse.MouseCoords.y);
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
				m_MouseIcon->SetTextAlpha(0);

				break;
			case SDL_WINDOWEVENT_ENTER:
				m_MouseIcon->SetTextAlpha(255);

				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (Event.button.button == SDL_BUTTON_LEFT)
			{
				if (m_MenuButtons["Start"]->MouseRelease(m_State, InMenu))
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

				if (m_MenuButtons["Settings"]->MouseRelease(m_State, InMenu))
				{
					ThemeActivate();

					break;
				}

				if (m_MenuButtons["Quit"]->MouseRelease(m_State, InMenu))
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
	m_MenuButtons["Start"]->SetColour(ButtonsAnim->Result);
	m_MenuButtons["Settings"]->SetColour(ButtonsAnim->Result);
	m_MenuButtons["Quit"]->SetColour(ButtonsAnim->Result);

	m_Title1->SetTextColour(TextAnim->Result);
	m_Timer->SetTextColour(TextAnim->Result);

	m_MenuButtons["Title"]->SetTextColour(TextAnim->Result);
	m_MenuButtons["Credits"]->SetTextColour(TextAnim->Result);
	m_MenuButtons["Start"]->SetTextColour(TextAnim->Result);
	m_MenuButtons["Settings"]->SetTextColour(TextAnim->Result);
	m_MenuButtons["Quit"]->SetTextColour(TextAnim->Result);

	SDL_SetRenderDrawColor(Window.Renderer, BackgroundAnim->Result.r, BackgroundAnim->Result.g, BackgroundAnim->Result.b, 255);

	SDL_RenderClear(Window.Renderer);

	if (m_State == InMenu)
	{
		for (const auto& Button : m_MenuButtons)
		{
			Button.second->Render();
		}
	}
	else if (m_State == InGame)
	{
		m_Grid->Render();
		m_SidePanel->Render();
		m_Title1->Render();
		m_Timer->Render();
		m_MouseIcon->Render();
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
 