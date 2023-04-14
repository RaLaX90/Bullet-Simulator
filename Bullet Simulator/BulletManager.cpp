#include "BulletManager.hpp"

BulletManager::BulletManager()
{

}

BulletManager::~BulletManager()
{

}

void BulletManager::Update(float time)
{
	for (auto i = 0; i < bullets.size(); ++i)
	{
		bullets[i]->Draw(m_renderer);
	}
}

void BulletManager::Fire(SDL_FPoint pos, SDL_FPoint dir, float speed, float time, float life_time)
{
	bullets.push_back(std::make_unique<Bullet>());
}

void BulletManager::DrawAllBullets(SDL_Renderer* m_renderer)
{
	for (auto i = 0; i < bullets.size(); ++i)
	{
		bullets[i]->Draw(m_renderer);
	}
}