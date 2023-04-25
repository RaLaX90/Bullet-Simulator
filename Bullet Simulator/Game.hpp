#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <memory>
#include <string>

#include "Window.hpp"
//#include "Audio.hpp"
#include "BulletManager.hpp"
#include "WallManager.hpp"

#include "Global.hpp"

class Game
{
public:
	enum State {
		STATE_OK = 0,
		STATE_EXIT,
		STATE_PAUSE
	};

private:
	State m_state;

	std::unique_ptr<BulletManager> m_bulletManager;
	std::unique_ptr<WallManager> m_wallManager;

	SDL_Event m_event;

	unsigned int m_frameCount = 0, m_actualFPS = 0;
	float m_timerFPS = 0;

	uint32_t m_begin = SDL_GetTicks(), m_end;
	float m_elapsed_secs;

	TTF_Font* m_fps_font;
	SDL_Rect m_fps_rect;

	int m_elements_count;

	void DrawFPS(const SDL_Renderer* _renderer);

public:
	Game(int elements_count);
	~Game();

	void Fire(const SDL_Renderer* _renderer, SDL_FPoint pos, SDL_FPoint dir, float speed, float time, float life_time);

	void CalculateFPS();
	void Update();
	void HandleEvents();
	void DrawAll();

	State GetState() const;
};