#include "Bullet.hpp"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::Draw(SDL_Renderer* m_renderer)
{
	if (SDL_RenderCopyF(m_renderer, image, nullptr, &position_and_size))  //0 is a success
	{
		throw SDL_GetError();
	}
}