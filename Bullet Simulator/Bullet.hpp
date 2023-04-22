#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Bullet
{
private:
	SDL_FPoint direction;
	float speed;
	float time_to_appearse;
	float life_time;

	SDL_Texture* image;
	SDL_FRect position_and_size;

public:
	Bullet(SDL_Renderer* _renderer, const SDL_FRect& position_and_size, const SDL_FPoint& direction, const float& speed, const float& time_to_appearse, const float& life_time);
	~Bullet();

	void Update(float time);
	void Draw(SDL_Renderer* m_renderer) const;
};