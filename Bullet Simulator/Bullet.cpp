#include "Bullet.hpp"

Bullet::Bullet(SDL_Renderer* _renderer, const SDL_FRect& position_and_size, const SDL_FPoint& direction, const float& speed, const float& time_to_appearse, const float& life_time):
	position_and_size(position_and_size), direction(direction), speed(speed), time_to_appearse(time_to_appearse), life_time(life_time)
{
	this->image = IMG_LoadTexture(_renderer, "../data/icons/bullet.png");
	if (!image)
	{
		throw "Error at load image";
	}
}

Bullet::~Bullet()
{
	SDL_DestroyTexture(image);
}

void Bullet::Update(float time)
{
	position_and_size.x += direction.x * (speed * time);
	position_and_size.y += direction.y * (speed * time);
}

void Bullet::Draw(SDL_Renderer* m_renderer) const
{
	if (SDL_RenderCopyF(m_renderer, image, nullptr, &position_and_size))  //0 is a success
	{
		throw SDL_GetError();
	}
}