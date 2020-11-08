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



void MapArea::moveTo(const MapCoordinates& left)
{
    this->left = left;
}



MapArea::ConstIterator MapArea::begin() const
{
    return { left, getRight() };
}



MapArea::ConstIterator MapArea::end() const
{
    return ConstIterator(left, getRight()).toEnd();
}



QString MapArea::toString() const
{
    return '{' + left.toString() + ';' + QString::number(size.getValue()) + '}';
}



MapArea::ConstIterator::ConstIterator(const MapCoordinates& left, const MapCoordinates& right) :
    xMin(left.getX()),
    xMax(right.getX()),
    yMin(left.getY()),
    yMax(right.getY()),
    x(xMin),
    y(yMin)
{

}



const MapArea::ConstIterator& MapArea::ConstIterator::operator ++()
{
    ++x;
    if (x > xMax) {
        x = xMin;
        ++y;
    }

    return *this;
}



MapCoordinates MapArea::ConstIterator::operator *() const
{
    return { x, y };
}



bool MapArea::ConstIterator::operator !=(const MapArea::ConstIterator& other) const
{
    return
        xMin != other.xMin || xMax != other.xMax ||
        yMin != other.yMin || yMax != other.yMax ||
        x != other.x || y != other.y;
}



const MapArea::ConstIterator& MapArea::ConstIterator::toEnd()
{
    x = xMin;
    y = yMax + 1;

    return *this;
}
