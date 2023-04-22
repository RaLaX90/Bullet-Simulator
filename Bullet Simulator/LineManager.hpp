#pragma once

#include <SDL.h>

#include <vector>
#include <memory>

#include "Line.hpp"

class LineManager
{
private:
	std::vector<std::unique_ptr<Line>> lines{ };

	int m_elements_count;

public:
	LineManager(int elements_count);
	~LineManager();

	void AddNewLine(const FLineCoordinate& line_coordinate);
	void DrawAllLines(SDL_Renderer* m_renderer) const;

	const std::vector<std::unique_ptr<Line>>* GetLinesPointer() const;
};