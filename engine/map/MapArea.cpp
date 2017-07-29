#include "MapArea.hpp"

#include <QString>



MapArea::MapArea() :
    size(),
    left()
{

}



MapArea::MapArea(const MapCoordinates& left) :
    size(),
    left(left)
{

}



MapArea::MapArea(const MapCoordinates& left, const MapSize& size) :
    size(size),
    left(left)
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
    int deltaSize(size.getValue() - 1);
    return { left.getX() + deltaSize, left.getY() + deltaSize };
}



MapCoordinates MapArea::getTop() const
{
    int deltaSize(size.getValue() - 1);
    return { left.getX() + deltaSize, left.getY() };
}



MapCoordinates MapArea::getBottom() const
{
    int deltaSize(size.getValue() - 1);
    return { left.getX(), left.getY() + deltaSize };
}



bool MapArea::isInside(const MapCoordinates& coordinates) const
{
    auto right(getRight());
    return coordinates.getX() >= left.getX() && coordinates.getX() <= right.getX()
            && coordinates.getY() >= left.getY() && coordinates.getY() <= right.getY();
}



QString MapArea::toString() const
{
    return '{' + left.toString() + ';' + QString::number(size.getValue()) + '}';
}
