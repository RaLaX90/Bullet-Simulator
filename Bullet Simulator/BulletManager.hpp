#pragma once

#include <SDL.h>

#include <memory>
#include <vector>

#include "Bullet.hpp"
#include "Window.hpp"
#include "Line.hpp"

class BulletManager
{
private:
	std::vector<std::unique_ptr<Bullet>> bullets{ };
	const std::vector<std::unique_ptr<Line>>* lines;

	int m_elements_count;

public:
	BulletManager(int elements_count, const std::vector<std::unique_ptr<Line>>* lines);
	~BulletManager();

	void Update(float time);
	void Fire(SDL_FPoint pos, SDL_FPoint dir, float speed, float time, float life_time);
	void DrawAllBullets(SDL_Renderer* m_renderer);
};