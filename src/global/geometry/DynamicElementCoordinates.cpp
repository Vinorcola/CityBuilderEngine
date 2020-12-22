#include "DynamicElementCoordinates.hpp"

#include "src/global/geometry/TileCoordinates.hpp"



DynamicElementCoordinates::DynamicElementCoordinates(qreal x, qreal y) :
    _x(x),
    _y(y)
{

}



bool DynamicElementCoordinates::operator ==(const DynamicElementCoordinates& other) const
{
    return _x == other._x && _y == other._y;
}



qreal DynamicElementCoordinates::x() const
{
    return _x;
}



qreal DynamicElementCoordinates::y() const
{
    return _y;
}



TileCoordinates DynamicElementCoordinates::associatedTileCoordinates() const
{
    return { qRound(_x), qRound(_y) };
}
