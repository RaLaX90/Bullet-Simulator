#include "Wall.hpp"

Wall::Wall(const FWallCoordinate& coordinate)
{
	this->coordinate.X1 = coordinate.X1;
	this->coordinate.X2 = coordinate.X2;
	this->coordinate.Y1 = coordinate.Y1;
	this->coordinate.Y2 = coordinate.Y2;
}

Wall::~Wall()
{

}

void Wall::SetCoordinate(const FWallCoordinate* coordinate)
{
	this->coordinate = *coordinate;
}

const FWallCoordinate* Wall::GetCoordinatePointer() const
{
	return &coordinate;
}

void Wall::Draw(const SDL_Renderer* m_renderer) const
{
	SDL_RenderDrawLineF(const_cast<SDL_Renderer*>(m_renderer), coordinate.X1, coordinate.Y1, coordinate.X2, coordinate.Y2);

	// commented for optimization
	//if (SDL_RenderDrawLineF(const_cast<SDL_Renderer*>(m_renderer), coordinate.X1, coordinate.Y1, coordinate.X2, coordinate.Y2))  //0 is a success
	//{
	//	throw SDL_GetError();
	//}
}