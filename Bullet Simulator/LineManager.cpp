#include "LineManager.hpp"

LineManager::LineManager(int elements_count) :
	m_elements_count(elements_count)
{
	lines.reserve(m_elements_count);
}

LineManager::~LineManager()
{

}

void LineManager::AddNewLine(const FLineCoordinate& line_coordinate)
{
	lines.emplace_back(std::make_unique<Line>(line_coordinate));
}

void LineManager::DrawAllLines(SDL_Renderer* m_renderer) const
{
	for (const auto& line : lines) {
		if (line) {
			line->Draw(m_renderer);
		}
	}
}

const std::vector<std::unique_ptr<Line>>* LineManager::GetLinesPointer() const
{
	return &lines;
}