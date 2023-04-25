#pragma once

#include <SDL.h>

struct FWallCoordinate {
	float X1;
	float Y1;
	float X2;
	float Y2;
};

class Wall
{
private:
	FWallCoordinate coordinate;

public:
	Wall(const FWallCoordinate& coordinate);
	~Wall();

	void SetCoordinate(const FWallCoordinate* coordinate);
	const FWallCoordinate* GetCoordinatePointer() const;

	void Draw(const SDL_Renderer* m_renderer) const;
};