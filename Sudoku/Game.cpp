#include "Game.h"

#include "Window.h"

Uint32 Game::m_MouseButtons = Uint32();
SDL_Point Game::m_MouseCoords = SDL_Point();

Game::Game()
{
	m_Running = true;

	Buttons.push_back(Start = new Button(200, 50, 640, 360, 0.5f, 0.5f));
	Start->SetColour({ 255, 255, 255, 255 });

	Sudoku Board;
	Board.CreateSeed();
	Board.GeneratePuzzle();
	Board.CalculateDifficulty();
	Board.PrintGrid();
}

void Game::Tick()
{
	Start->Update();
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
				for (auto Button : Buttons)
				{
					if (Button->GetFocusable())
					{
						Button->MouseRelease();
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

	Start->Render();

	SDL_RenderPresent(Window::m_Renderer);
}

bool Game::GetRunning()
{
	return m_Running;
}
 