#include "BulletManager.hpp"

bool BulletManager::isCollision(const SDL_FRect* bullet_coordinate, const FWallCoordinate* wall_coordinate) const
{
	auto wall_coordinate_non_const = const_cast<FWallCoordinate*>(wall_coordinate);
	return SDL_IntersectFRectAndLine(bullet_coordinate, &wall_coordinate_non_const->X1, &wall_coordinate_non_const->Y1, &wall_coordinate_non_const->X2, &wall_coordinate_non_const->Y2);
}

void BulletManager::Fire(const SDL_Renderer* _renderer, SDL_FPoint pos, SDL_FPoint dir, float speed, float time, float life_time)
{
	//Window* window = Window::GetInstance(MAP_WIDTH, MAP_HEIGHT);

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

	m_generator = std::mt19937(m_rd());
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
}

void BulletManager::Update(float time)
{
	for (const auto& bullet : bullets) {
		if (bullet) {
			if (bullet->GetLifeTime() > time) {
				bullet->SetLifeTime(bullet->GetLifeTime() - time);

				bullet->Update(time);

				for (const auto& wall : *walls) {
					if (wall) {
						if (isCollision(bullet->GetPositionAndSizePointer(), wall->GetCoordinatePointer())) {
							SDL_FPoint bulletCenterTop = { bullet->GetPositionAndSizePointer()->x + 7.5F , bullet->GetPositionAndSizePointer()->y };
							SDL_FPoint bulletCenterBottom = { bullet->GetPositionAndSizePointer()->x + 7.5F, bullet->GetPositionAndSizePointer()->y + 15.0F };
							SDL_FPoint bulletCenterLeft = { bullet->GetPositionAndSizePointer()->x, bullet->GetPositionAndSizePointer()->y + 7.5F };
							SDL_FPoint bulletCenterRight = { bullet->GetPositionAndSizePointer()->x + 15.0F, bullet->GetPositionAndSizePointer()->y + 7.5F };

							float distanceRightToWallX = abs(bulletCenterRight.x - wall->GetCoordinatePointer()->X1);
							float distanceRightToWallY = abs(bulletCenterRight.y - wall->GetCoordinatePointer()->Y1);
							float distanceLeftToWallX = abs(bulletCenterLeft.x - wall->GetCoordinatePointer()->X1);
							float distanceLeftToWallY = abs(bulletCenterLeft.y - wall->GetCoordinatePointer()->Y1);
							float distanceTopToWallX = abs(bulletCenterTop.x - wall->GetCoordinatePointer()->X1);
							float distanceTopToWallY = abs(bulletCenterTop.y - wall->GetCoordinatePointer()->Y1);
							float distanceBottomToWallX = abs(bulletCenterBottom.x - wall->GetCoordinatePointer()->X1);
							float distanceBottomToWallY = abs(bulletCenterBottom.y - wall->GetCoordinatePointer()->Y1);

							// Collision of the top side of the bullet against the wall
							if (bullet->GetDirection().y < 0 && distanceTopToWallY < distanceBottomToWallY && distanceTopToWallY < distanceRightToWallY && distanceTopToWallY < distanceLeftToWallY)
							{
								bullet->SetDirectionY(abs(bullet->GetDirection().y));
							}
							// Collision of the bottom side of the bullet against the wall
							else if (bullet->GetDirection().y > 0 && distanceBottomToWallY < distanceTopToWallY && distanceBottomToWallY < distanceRightToWallY && distanceBottomToWallY < distanceLeftToWallY)
							{
								bullet->SetDirectionY(-abs(bullet->GetDirection().y));
							}
							// Collision of the left side of the bullet against the wall
							else if (bullet->GetDirection().x > 0 && distanceRightToWallX < distanceLeftToWallX && distanceRightToWallX < distanceTopToWallX && distanceRightToWallX < distanceBottomToWallX)
							{
								bullet->SetDirectionX(-abs(bullet->GetDirection().x));
							}
							// Collision of the right side of the bullet against the wall
							else if (bullet->GetDirection().x < 0 && distanceLeftToWallY < distanceRightToWallX && distanceLeftToWallY < distanceTopToWallX && distanceLeftToWallY < distanceBottomToWallX)
							{
								bullet->SetDirectionX(abs(bullet->GetDirection().x));
							}

							const_cast<std::unique_ptr<Wall>&>(wall).reset();	// yeah, i know - it's a crutch
						}
					}
				}
			}
			else {
				const_cast<std::unique_ptr<Bullet>&>(bullet).reset();			//this too
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