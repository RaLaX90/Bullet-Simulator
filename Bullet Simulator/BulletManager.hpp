#pragma once

#include <SDL.h>
#include "Bullet.hpp"

#include <memory>
#include <vector>

class BulletManager
{
private:
	std::vector<std::unique_ptr<Bullet>> bullets{ 10, nullptr };

public:
	BulletManager();
	~BulletManager();

	void Update(float time);
	void Fire(SDL_FPoint pos, SDL_FPoint dir, float speed, float time, float life_time);
	void DrawAllBullets(SDL_Renderer* m_renderer);
};