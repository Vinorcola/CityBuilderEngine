#include "TileArea.hpp"

#include "src/global/geometry/TileCoordinates.hpp"



TileArea::Iterator::Iterator(const TileCoordinates& left, const TileCoordinates& right) :
    LEFT(left),
    RIGHT(right),
    x(left.x()),
    y(left.y())
{

}



TileArea::Iterator TileArea::Iterator::CreateEnd(
    const TileCoordinates& left,
    const TileCoordinates& right
) {
    Iterator iterator(left, right);
    iterator.y = right.y() + 1;

    return iterator;
}



const TileArea::Iterator& TileArea::Iterator::operator ++()
{
    ++x;
    if (x > RIGHT.x()) {
        x = LEFT.x();
        ++y;
    }

    return *this;
}



TileCoordinates TileArea::Iterator::operator *() const
{
    return { x, y };
}



bool TileArea::Iterator::operator !=(const TileArea::Iterator& other) const
{
    return x != other.x || y != other.y;
}



TileArea::TileArea(const TileCoordinates& leftCorner, const TileAreaSize& size) :
    _leftCorner(leftCorner),
    _size(size)
{

}



const TileAreaSize& TileArea::size() const
{
    return _size;
}



const TileCoordinates& TileArea::leftCorner() const
{
    return _leftCorner;
}



TileCoordinates TileArea::resolveTopCorner() const
{
    return { _leftCorner.x() + _size.width() - 1, _leftCorner.y() };
}



TileCoordinates TileArea::resolveRightCorner() const
{
    return { _leftCorner.x() + _size.width() - 1, _leftCorner.y() + _size.height() - 1 };
}



TileCoordinates TileArea::resolveBottomCorner() const
{
    return { _leftCorner.x(), _leftCorner.y() + _size.height() - 1 };
}



void TileArea::moveTo(const TileCoordinates& leftCorner)
{
    _leftCorner = leftCorner;
}



TileArea::Iterator TileArea::begin() const
{
    return {
        _leftCorner,
        { _leftCorner.x() + _size.width() - 1, _leftCorner.y() + _size.height() - 1 },
    };
}



TileArea::Iterator TileArea::beginAfterLeftCorner() const
{
    auto iterator(begin());
    ++iterator;

    return iterator;
}



TileArea::Iterator TileArea::end() const
{
    return Iterator::CreateEnd(
        _leftCorner,
        { _leftCorner.x() + _size.width() - 1, _leftCorner.y() + _size.height() - 1 }
                );
}



QString TileArea::toString() const
{
    return '{' + _leftCorner.hash() + ';' + _size.toString() + '}';
}
