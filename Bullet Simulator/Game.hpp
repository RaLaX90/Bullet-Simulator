#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include <SDL_mixer.h>

//#include <random>
#include <memory>

#include "Window.hpp"
#include "Audio.hpp"

#include "Global.hpp"
#include "BulletManager.hpp"

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

	std::uint32_t current_time;

	std::unique_ptr<BulletManager> bulletManager;

	SDL_Event event;

	uint16_t m_actual_fps;		// current FPS.
	uint8_t m_desired_fps;		// The desired FPS for the game.

	//std::random_device m_rd;
	//std::mt19937 m_generator;											// generator for distribution
	//std::uniform_int_distribution<short> m_distribution_screen_width;	// object for random distribution of m_screen_width
	//std::uniform_int_distribution<short> m_distribution_screen_height;	// object for random distribution of m_screen_height

	//std::uniform_int_distribution<short> m_distribution_direction_x;
	//std::uniform_int_distribution<short> m_distribution_direction_y;

	bool isCollision(const SDL_Rect* object1, const SDL_Rect* object2) const;

public:
	Game();
	~Game();

	void Update();
	void HandleEvents();
	void DrawAll();

	State GetState() const;
};