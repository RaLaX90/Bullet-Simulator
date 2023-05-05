#include "BulletManager.hpp"
#include <algorithm>
#include <iostream>
#include <string>

bool BulletManager::isCollision(const SDL_FRect* bullet_coordinate, const FWallCoordinate* wall_coordinate) const
{
	auto wall_coordinate_non_const = const_cast<FWallCoordinate*>(wall_coordinate);
	return SDL_IntersectFRectAndLine(bullet_coordinate, &wall_coordinate_non_const->X1, &wall_coordinate_non_const->Y1, &wall_coordinate_non_const->X2, &wall_coordinate_non_const->Y2);
}

void BulletManager::Fire(const SDL_Renderer* _renderer, SDL_FPoint pos, SDL_FPoint dir, float speed, float time, float life_time)
{
	bullets.emplace_back(
		std::make_unique<Bullet>(
			_renderer, SDL_FRect{ pos.x, pos.y, BULLET_WIDTH, BULLET_HEIGHT }, dir, speed, time, life_time
		)
	);
}

BulletManager::BulletManager(int elements_count, const std::vector<std::unique_ptr<Wall>>* walls) :
	walls(walls)
{
	bullets.reserve(elements_count);

	m_generator.seed(std::random_device()());
	m_distribution_bullet_direction_X = std::uniform_real_distribution<float>(-180.0F, 180.0F);
	m_distribution_bullet_direction_Y = std::uniform_real_distribution<float>(-180.0F, 180.0F);
}

BulletManager::~BulletManager()
{

}

void BulletManager::AddBullets()
{
	Window* window = Window::GetInstance(MAP_WIDTH, MAP_HEIGHT);

	for (float i = 0; i < bullets.capacity(); ++i) {
		this->Fire(
			window->GetRenderer(),
			SDL_FPoint{ (MAP_WIDTH / 2) - (BULLET_WIDTH / 2), (MAP_HEIGHT / 2) - (BULLET_HEIGHT / 2) },  //spawn bullet in center of window
			SDL_FPoint{ m_distribution_bullet_direction_X(m_generator),m_distribution_bullet_direction_Y(m_generator) }, // randomize bullet direction
			BULLET_SPEED,
			i,
			BULLET_LIFE_TIME
		);
	}

	maxLeftBulletIterator = bullets.begin();
	maxRightBulletIterator = bullets.begin();
	maxTopBulletIterator = bullets.begin();
	maxBottomBulletIterator = bullets.begin();
}

void BulletManager::Update(float time)
{
	for (auto it = bullets.begin(); it != bullets.end(); ++it) {
		if (*it) {
			if ((*it)->GetLifeTime() > time) {
				(*it)->SetLifeTime((*it)->GetLifeTime() - time);

				(*it)->Update(time);

				if ((*it)->GetPositionAndSizePointer()->x < (*(this->maxLeftBulletIterator))->GetPositionAndSizePointer()->x) {
					this->maxLeftBulletIterator = it;
				}
				else if ((*it)->GetPositionAndSizePointer()->x > (*(this->maxRightBulletIterator))->GetPositionAndSizePointer()->x) {
					this->maxRightBulletIterator = it;
				}

				if ((*it)->GetPositionAndSizePointer()->y < (*(this->maxTopBulletIterator))->GetPositionAndSizePointer()->y) {
					this->maxTopBulletIterator = it;
				}
				else if ((*it)->GetPositionAndSizePointer()->y > (*(this->maxBottomBulletIterator))->GetPositionAndSizePointer()->y) {
					this->maxBottomBulletIterator = it;
				}
			}
			else {
				const_cast<std::unique_ptr<Bullet>&>(*it).reset();			//this too
			}
		}
	}

	std::vector<std::vector<std::unique_ptr<Bullet>>::iterator> iterators{ maxLeftBulletIterator, maxRightBulletIterator, maxTopBulletIterator, maxBottomBulletIterator };

	for (const auto& iterator : iterators) {
		if (*iterator) {
			for (const auto& wall : *walls) {
				if (wall) {
					if (isCollision((*iterator)->GetPositionAndSizePointer(), wall->GetCoordinatePointer())) {
						SDL_FPoint bulletCenterTop = { (*iterator)->GetPositionAndSizePointer()->x + 7.5F , (*iterator)->GetPositionAndSizePointer()->y };
						SDL_FPoint bulletCenterBottom = { (*iterator)->GetPositionAndSizePointer()->x + 7.5F, (*iterator)->GetPositionAndSizePointer()->y + 15.0F };
						SDL_FPoint bulletCenterLeft = { (*iterator)->GetPositionAndSizePointer()->x, (*iterator)->GetPositionAndSizePointer()->y + 7.5F };
						SDL_FPoint bulletCenterRight = { (*iterator)->GetPositionAndSizePointer()->x + 15.0F, (*iterator)->GetPositionAndSizePointer()->y + 7.5F };

						float distanceRightToWallX = abs(bulletCenterRight.x - wall->GetCoordinatePointer()->X1);
						float distanceRightToWallY = abs(bulletCenterRight.y - wall->GetCoordinatePointer()->Y1);
						float distanceLeftToWallX = abs(bulletCenterLeft.x - wall->GetCoordinatePointer()->X1);
						float distanceLeftToWallY = abs(bulletCenterLeft.y - wall->GetCoordinatePointer()->Y1);
						float distanceTopToWallX = abs(bulletCenterTop.x - wall->GetCoordinatePointer()->X1);
						float distanceTopToWallY = abs(bulletCenterTop.y - wall->GetCoordinatePointer()->Y1);
						float distanceBottomToWallX = abs(bulletCenterBottom.x - wall->GetCoordinatePointer()->X1);
						float distanceBottomToWallY = abs(bulletCenterBottom.y - wall->GetCoordinatePointer()->Y1);

						// Collision of the top side of the bullet against the wall
						if ((*iterator)->GetDirection().y < 0 && distanceTopToWallY < distanceBottomToWallY && distanceTopToWallY < distanceRightToWallY && distanceTopToWallY < distanceLeftToWallY)
						{
							(*iterator)->SetDirectionY(abs((*iterator)->GetDirection().y));
						}
						// Collision of the bottom side of the bullet against the wall
						else if ((*iterator)->GetDirection().y > 0 && distanceBottomToWallY < distanceTopToWallY && distanceBottomToWallY < distanceRightToWallY && distanceBottomToWallY < distanceLeftToWallY)
						{
							(*iterator)->SetDirectionY(-abs((*iterator)->GetDirection().y));
						}
						// Collision of the left side of the bullet against the wall
						else if ((*iterator)->GetDirection().x > 0 && distanceRightToWallX < distanceLeftToWallX && distanceRightToWallX < distanceTopToWallX && distanceRightToWallX < distanceBottomToWallX)
						{
							(*iterator)->SetDirectionX(-abs((*iterator)->GetDirection().x));
						}
						// Collision of the right side of the bullet against the wall
						else if ((*iterator)->GetDirection().x < 0 && distanceLeftToWallY < distanceRightToWallX && distanceLeftToWallY < distanceTopToWallX && distanceLeftToWallY < distanceBottomToWallX)
						{
							(*iterator)->SetDirectionX(abs((*iterator)->GetDirection().x));
						}

						const_cast<std::unique_ptr<Wall>&>(wall).reset();	// yeah, i know - it's a crutch
					}
				}
			}
		}
	}
}

void BulletManager::DrawAll(const SDL_Renderer* m_renderer) const
{
	for (const auto& bullet : bullets) {
		if (bullet) {
			bullet->Draw(m_renderer);
		}
	}
}