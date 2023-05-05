#pragma once

//#include <SDL.h>

//#include <memory>
//#include <vector>
//#include <cmath>
#include <random>

#include "Bullet.hpp"
#include "Window.hpp"
#include "Wall.hpp"

#include "Global.hpp"

class BulletManager
{
private:
	std::vector<std::unique_ptr<Bullet>> bullets;
	const std::vector<std::unique_ptr<Wall>>* walls;

	std::vector<std::unique_ptr<Bullet>>::iterator maxLeftBulletIterator;
	std::vector<std::unique_ptr<Bullet>>::iterator maxRightBulletIterator;
	std::vector<std::unique_ptr<Bullet>>::iterator maxTopBulletIterator;
	std::vector<std::unique_ptr<Bullet>>::iterator maxBottomBulletIterator;

	std::mt19937 m_generator;													// generator for distribution
	std::uniform_real_distribution<float> m_distribution_bullet_direction_X;	// object for random distribution of m_screen_width
	std::uniform_real_distribution<float> m_distribution_bullet_direction_Y;	// object for random distribution of m_screen_height

	bool isCollision(const SDL_FRect* bullet_coordinate, const FWallCoordinate* wall_coordinate) const;

public:
	BulletManager(int elements_count, const std::vector<std::unique_ptr<Wall>>* walls);
	~BulletManager();

	void AddBullets();

	void Fire(const SDL_Renderer* _renderer, SDL_FPoint pos, SDL_FPoint dir, float speed, float time, float life_time);

	void Update(float time);
	void DrawAll(const SDL_Renderer* m_renderer) const;
};