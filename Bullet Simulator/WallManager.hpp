#pragma once

#include <SDL.h>

#include <vector>
#include <memory>

#include "Wall.hpp"

#include "Global.hpp"

class WallManager
{
private:
	std::vector<std::unique_ptr<Wall>> walls{ };

public:
	WallManager(int elements_count);
	~WallManager();

	void AddWalls();
	void DrawAll(const SDL_Renderer* m_renderer) const;

	const std::vector<std::unique_ptr<Wall>>* GetWallsPointer() const;
};