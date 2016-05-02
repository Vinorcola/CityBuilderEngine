#include "MapElement.hpp"





bool MapCoordinates::operator==(const MapCoordinates& other) const
{
    return coordinates.x() == other.coordinates.x() && coordinates.y() == other.coordinates.y();
}





bool MapCoordinates::operator!=(const MapCoordinates& other) const
{
    return coordinates.x() != other.coordinates.x() || coordinates.y() != other.coordinates.y();
}





int MapCoordinates::getX() const
{
    return coordinates.x();
}





int MapCoordinates::getY() const
{
    return coordinates.y();
}





void MapCoordinates::setX(const int x)
{
    coordinates.setX(x);
}





void MapCoordinates::setY(const int y)
{
    coordinates.setY(y);
}





MapCoordinates MapCoordinates::getNorth() const
{
    return { coordinates.x(), coordinates.y() - 1 };
}





MapCoordinates MapCoordinates::getSouth() const
{
    return { coordinates.x(), coordinates.y() + 1 };
}





MapCoordinates MapCoordinates::getEast() const
{
    return { coordinates.x() + 1, coordinates.y() };
}





MapCoordinates MapCoordinates::getWest() const
{
    return { coordinates.x() - 1, coordinates.y() };
}





MapArea::MapArea() :
    size(),
    left()
{
    
}





MapArea::MapArea(const MapCoordinates& left, const MapSize& size) :
    size(size),
    left(left),
    right(left.getX() + size.getSize() - 1, left.getY() + size.getSize() - 1)
{
    
}





const MapSize MapArea::getSize() const
{
    return size;
}





const MapCoordinates& MapArea::getLeft() const
{
    return left;
}





MapCoordinates MapArea::getRight() const
{
    int deltaSize(size.getSize() - 1);
    return { left.getX() + deltaSize, left.getY() + deltaSize };
}





MapCoordinates MapArea::getTop() const
{
    int deltaSize(size.getSize() - 1);
    return { left.getX() + deltaSize, left.getY() };
}





MapCoordinates MapArea::getBottom() const
{
    int deltaSize(size.getSize() - 1);
    return { left.getX(), left.getY() + deltaSize };
}





bool MapArea::isInside(const MapCoordinates& coordinates) const
{
    return coordinates.getX() >= left.getX() && coordinates.getX() <= right.getX()
        && coordinates.getY() >= left.getY() && coordinates.getY() <= right.getY();
}
