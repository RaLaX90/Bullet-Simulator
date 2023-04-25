#pragma once

//#include <SDL.h>
#include "SDL_image.h"

class Window // singleton "window" class
{
private:
	Window(short map_width, short map_height);
	~Window();

	static Window* m_window;

	unsigned short m_map_width = 0, m_map_height = 0;

	const SDL_Window* m_sdl_window = nullptr;
	const SDL_Renderer* m_renderer = nullptr;

public:
	Window(Window& other) = delete;
	void operator=(const Window&) = delete;

	static Window* GetInstance(short map_width, short map_height);

	const SDL_Renderer* GetRenderer() const;
};