#include "Window.hpp"

Window* Window::m_window = nullptr;

Window::Window(short map_width, short map_height) :
	m_map_width(map_width), m_map_height(map_height) {

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	auto screen_width = DM.w;
	auto screen_height = DM.h;

	this->m_sdl_window = SDL_CreateWindow("Bullet Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_map_width, m_map_height,
		screen_width <= m_map_width && screen_height <= m_map_height ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE
	);
	if (m_sdl_window == nullptr) {
		throw SDL_GetError();
	}

	this->m_renderer = SDL_CreateRenderer(const_cast<SDL_Window*>(m_sdl_window), -1, SDL_RENDERER_ACCELERATED
		//| SDL_RENDERER_PRESENTVSYNC //limit to 60/120 fps
	);
	if (m_renderer == nullptr) {
		throw "Error at renderer create";
	}
}

Window::~Window() {
	SDL_DestroyRenderer(const_cast<SDL_Renderer*>(m_renderer));
	SDL_DestroyWindow(const_cast<SDL_Window*>(m_sdl_window));
}

Window* Window::GetInstance(short map_width, short map_height)
{
	if (m_window == nullptr) {
		m_window = new Window(map_width, map_height);
	}

	return m_window;
}

const SDL_Renderer* Window::GetRenderer() const
{
	return m_renderer;
}