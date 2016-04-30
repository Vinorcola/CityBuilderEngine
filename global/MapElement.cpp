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





bool MapArea::isInside(const MapCoordinates& coordinates) const
{
    return coordinates.getX() >= left.getX() && coordinates.getX() <= right.getX()
        && coordinates.getY() >= left.getY() && coordinates.getY() <= right.getY();
}
