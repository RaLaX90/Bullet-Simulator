#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include <SDL_mixer.h>

//#include <random>
#include <memory>

#include "Window.hpp"
#include "Audio.hpp"
#include "BulletManager.hpp"
#include "LineManager.hpp"

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
	State state;

	std::uint64_t current_time, last_update;

	std::unique_ptr<BulletManager> bulletManager;
	std::unique_ptr<LineManager> lineManager;

	SDL_Event event;

	uint16_t m_actual_fps;		// current FPS.
	uint8_t m_desired_fps;		// The desired FPS for the game.

	unsigned char m_fps;
	TTF_Font* m_fps_font;
	SDL_Rect m_fps_rect;

	int m_elements_count;

	//std::random_device m_rd;
	//std::mt19937 m_generator;											// generator for distribution
	//std::uniform_int_distribution<short> m_distribution_screen_width;	// object for random distribution of m_screen_width
	//std::uniform_int_distribution<short> m_distribution_screen_height;	// object for random distribution of m_screen_height

	//std::uniform_int_distribution<short> m_distribution_direction_x;
	//std::uniform_int_distribution<short> m_distribution_direction_y;

	void DrawScore(SDL_Renderer* _renderer, int fps);
	bool isCollision(const SDL_FRect* bullet_coordinate, FLineCoordinate* line_coordinate) const;

public:
	Game(int elements_count);
	~Game();

	void Fire(SDL_FPoint start_position, SDL_FPoint dirrection, float speed, float shot_time, float life_time);
	void AddLines(unsigned short window_center_X, unsigned short window_center_Y);

	void Update(float elapsed_secs);
	void HandleEvents();
	void DrawAll(int fps);

	State GetState() const;
};