#include "Window.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

SDL_Window* Window::m_Window = nullptr;
SDL_Renderer* Window::m_Renderer = nullptr;

int Window::m_Width = SCREEN_WIDTH;
int Window::m_Height = SCREEN_HEIGHT;

Window::Window()
{
    
}

Window::~Window()
{
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
}

bool Window::InitialiseWindow()
{
    m_Window = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    m_Renderer = CreateRenderer();

    return m_Window != nullptr && m_Renderer != nullptr;
}

SDL_Renderer* Window::CreateRenderer()
{
    return SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}
