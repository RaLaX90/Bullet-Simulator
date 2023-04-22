#include "Line.hpp"

Line::Line(const FLineCoordinate& coordinate)
{
	this->coordinate.X1 = coordinate.X1;
	this->coordinate.X2 = coordinate.X2;
	this->coordinate.Y1 = coordinate.Y1;
	this->coordinate.Y2 = coordinate.Y2;
}

Line::~Line()
{

}

FLineCoordinate Line::GetCoordinate() const
{
	return coordinate;
}

void Line::SetCoordinate(const FLineCoordinate& coordinate) const
{

}

void Line::Draw(SDL_Renderer* m_renderer)
{
	if (SDL_RenderDrawLineF(m_renderer, coordinate.X1, coordinate.Y1, coordinate.X2, coordinate.Y2))  //0 is a success
	{
		throw SDL_GetError();
	}
}