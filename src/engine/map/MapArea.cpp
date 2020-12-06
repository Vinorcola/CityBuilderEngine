#include "MapArea.hpp"

#include <cassert>
#include <QtCore/QSize>
#include <QtCore/QString>



MapArea::MapArea(const MapCoordinates& left, const MapSize& size) :
    left(left),
    right(left.getX() + size.getHeight() - 1, left.getY() + size.getWidth() - 1)
{

}



MapArea::MapArea(const MapCoordinates& left, const MapCoordinates& right) :
    left(left),
    right(right)
{
    assert(right.getX() >= left.getX());
    assert(right.getY() >= right.getX());
}



MapSize MapArea::getSize() const
{
    return {
        static_cast<int>(right.getX()) - static_cast<int>(left.getX()) + 1,
        static_cast<int>(right.getY()) - static_cast<int>(left.getY()) + 1,
    };
}



const MapCoordinates& MapArea::getLeft() const
{
    return left;
}



const MapCoordinates& MapArea::getRight() const
{
    return right;
}



MapCoordinates MapArea::getTop() const
{
    return { right.getY(), left.getY() };
}



MapCoordinates MapArea::getBottom() const
{
    return { left.getX(), right.getY() };
}



void MapArea::moveTo(const MapCoordinates& left)
{
    auto size(getSize());

    this->left = left;
    right.setX(left.getX() + size.getHeight() - 1);
    right.setY(left.getY() + size.getWidth() - 1);
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
    auto size(getSize());

    return '{' + left.toString() + ';' + size.toString() + '}';
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
