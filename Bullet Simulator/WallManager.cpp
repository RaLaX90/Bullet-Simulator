#include "WallManager.hpp"

WallManager::WallManager(int elements_count)
{
	walls.reserve(elements_count);
}

WallManager::~WallManager()
{

}

void WallManager::AddWalls()
{
	int step = 50;

	bool first = true, // I didn't come up with a working algorithm here)
		second = false,
		third = false,
		fourth = false;

	float window_center_X = MAP_WIDTH / 2;
	float window_center_Y = MAP_HEIGHT / 2;

	for (int i = 0; i < walls.capacity(); ++i) {
		if (first) {
			walls.emplace_back(
				std::make_unique<Wall>(FWallCoordinate{ window_center_X + step, window_center_Y - step, window_center_X + step, window_center_Y + step })
			);

			first = false;
			second = true;
		}
		else if (second) {
			walls.emplace_back(
				std::make_unique<Wall>(FWallCoordinate{ window_center_X + step, window_center_Y + step, window_center_X - step, window_center_Y + step })
			);

			second = false;
			third = true;
		}
		else if (third) {
			walls.emplace_back(
				std::make_unique<Wall>(FWallCoordinate{ window_center_X - step, window_center_Y + step, window_center_X - step, window_center_Y - step })
			);

			third = false;
			fourth = true;
		}
		else if (fourth) {
			walls.emplace_back(
				std::make_unique<Wall>(FWallCoordinate{ window_center_X - step, window_center_Y - step, window_center_X + step, window_center_Y - step })
			);

			fourth = false;
			first = true;

			step += 50;
		}
	}
}

void WallManager::DrawAll(const SDL_Renderer* m_renderer) const
{
	for (const auto& wall : walls) {
		if (wall) {
			wall->Draw(m_renderer);
		}
	}
}

const std::vector<std::unique_ptr<Wall>>* WallManager::GetWallsPointer() const
{
	return &walls;
}