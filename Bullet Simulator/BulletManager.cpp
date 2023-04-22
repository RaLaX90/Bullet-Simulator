#include "BulletManager.hpp"

BulletManager::BulletManager(int elements_count, const std::vector<std::unique_ptr<Line>>* lines) :
	m_elements_count(elements_count), lines(lines)
{
	bullets.reserve(m_elements_count);
}

BulletManager::~BulletManager()
{

}

void BulletManager::Update(float time)
{
	for (const auto& bullet : bullets) {
		if (bullet) {
			bullet->Update(time);
		}
	}
}

void BulletManager::Fire(SDL_FPoint pos, SDL_FPoint dir, float speed, float time, float life_time)
{
	Window* window = Window::GetInstance(1920, 1080, 1920, 1080);

	bullets.emplace_back(
		std::make_unique<Bullet>(
			window->GetRenderer(), SDL_FRect{ pos.x, pos.y, 15.0F, 15.0F }, dir, speed, time, life_time
		)
	);
}

void BulletManager::DrawAllBullets(SDL_Renderer* m_renderer)
{
	for (const auto& bullet : bullets) {
		if (bullet) {
			bullet->Draw(m_renderer);
		}
	}
}