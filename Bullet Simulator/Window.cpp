#include "Window.hpp"

Window* Window::m_window = nullptr;

// _width - playing field m_screen_width (x)
// _height - m_screen_height of the playing field (y)
Window::Window(short screen_width, short screen_height, short map_width, short map_height) :
	m_screen_width(screen_width), m_screen_height(screen_height), m_map_width(map_width), m_map_height(map_height) {

	//m_top_border_Y = (m_screen_height / 2) - (m_map_height / 2);
	//m_left_border_X = (m_screen_width / 2) - (m_map_width / 2);
	//m_bottom_border_Y = (m_screen_height / 2) + (m_map_height / 2);
	//m_right_border_X = (m_screen_width / 2) + (m_map_width / 2);

	m_sdl_window = SDL_CreateWindow("Bullet Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_screen_width, m_screen_height,
		m_screen_width == m_map_width && m_screen_height == m_map_height ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE
	);
	if (m_sdl_window == nullptr) {
		throw "Error at window create";
	}

	m_renderer = SDL_CreateRenderer(m_sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == nullptr) {
		throw "Error at renderer create";
	}
}

Window::~Window() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_sdl_window);
}

Window* Window::GetInstance(short screen_width, short screen_height, short map_width, short map_height)
{
	if (m_window == nullptr) {
		m_window = new Window(screen_width, screen_height, map_width, map_height);
	}
	return m_window;
}

unsigned short Window::GetScreenWidth() const
{
	return m_screen_width;
}

unsigned short Window::GetScreenHeight() const
{
	return m_screen_height;
}

unsigned short Window::GetMapWidth() const
{
	return m_map_width;
}

unsigned short Window::GetMapHeight() const
{
	return m_map_height;
}

//unsigned short Window::GetTopBorderY() const
//{
//	return m_top_border_Y;
//}
//
//unsigned short Window::GetLeftBorderX() const
//{
//	return m_left_border_X;
//}
//
//unsigned short Window::GetBottomBorderY() const
//{
//	return m_bottom_border_Y;
//}
//
//unsigned short Window::GetRightBorderX() const
//{
//	return m_right_border_X;
//}

SDL_Renderer* Window::GetRenderer() const
{
	return m_renderer;
}