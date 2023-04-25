#include "Bullet.hpp"

Bullet::Bullet(const SDL_Renderer* _renderer, const SDL_FRect& position_and_size, const SDL_FPoint& direction, const float& speed, const float& time_to_appearse, const float& life_time) :
	position_and_size(position_and_size), direction(direction), speed(speed), time_to_appearse(time_to_appearse), life_time(life_time)
{
	this->image = IMG_LoadTexture(const_cast<SDL_Renderer*>(_renderer), "../data/icons/bullet.png");
	if (!image)
	{
		throw IMG_GetError();
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

void Bullet::Draw(const SDL_Renderer* m_renderer) const
{
	SDL_RenderCopyF(const_cast<SDL_Renderer*>(m_renderer), image, nullptr, &position_and_size);

	// commented for optimization
	//if (SDL_RenderCopyF(const_cast<SDL_Renderer*>(m_renderer), image, nullptr, &position_and_size))  //0 is a success
	//{
	//	throw SDL_GetError();
	//}
}

const SDL_FRect* Bullet::GetPositionAndSizePointer() const
{
	return &position_and_size;
}

void Bullet::SetDirectionX(float new_direction_x)
{
	this->direction.x = new_direction_x;
}

void Bullet::SetDirectionY(float new_direction_y)
{
	this->direction.y = new_direction_y;
}

SDL_FPoint Bullet::GetDirection() const
{
	return direction;
}

void Bullet::SetLifeTime(float life_time)
{
	this->life_time = life_time;
}

float Bullet::GetLifeTime() const
{
	return life_time;
}