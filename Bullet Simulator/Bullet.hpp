#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Bullet
{
private:
	SDL_FPoint direction;
	float speed;
	//float time_to_appearse;
	float life_time;

	SDL_Texture* image;
	SDL_FRect position_and_size;

public:
	Bullet();
	~Bullet();

	void Draw(SDL_Renderer* m_renderer);
};