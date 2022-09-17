#include "Game.h"

#include "Window.h"

Uint32 Game::m_MouseButtons = Uint32();
SDL_Point Game::m_MouseCoords = SDL_Point();

Game::Game()
{
	m_Running = true;

	Start = new Button(200, 50, 640, 360, 0.5f, 0.5f);
	Start->SetColour({ 255, 0, 0, 255 });
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
 