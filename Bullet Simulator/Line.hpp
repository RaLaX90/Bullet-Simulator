#pragma once

#include <SDL.h>

struct FLineCoordinate {
	float X1;
	float Y1;
	float X2;
	float Y2;
};

class Line
{
private:
	FLineCoordinate coordinate;

public:
	Line(const FLineCoordinate& coordinate);
	~Line();

	FLineCoordinate GetCoordinate() const;
	void SetCoordinate(const FLineCoordinate& coordinate) const;

	void Draw(SDL_Renderer* m_renderer);
};