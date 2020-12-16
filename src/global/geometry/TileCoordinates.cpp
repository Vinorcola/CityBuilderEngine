#include "TileCoordinates.hpp"

#include <QtCore/QPoint>
#include <QtCore/QtMath>

#include "src/global/geometry/DynamicElementCoordinates.hpp"



TileCoordinates::TileCoordinates(int x, int y) :
    _x(x),
    _y(y),
    _hash(QString::number(x) + ';' + QString::number(y))
{

}



TileCoordinates::TileCoordinates(const TileCoordinates& other, const QPoint& offset) :
    _x(other.x() + offset.x()),
    _y(other.y() + offset.y()),
    _hash(QString::number(_x) + ';' + QString::number(_y))
{

}



bool TileCoordinates::operator ==(const TileCoordinates& other) const
{
    return _x == other._x && _y == other._y;
}



bool TileCoordinates::operator !=(const TileCoordinates& other) const
{
    return _x != other._x || _y != other._y;
}



int TileCoordinates::x() const
{
    return _x;
}



int TileCoordinates::y() const
{
    return _y;
}



const QString& TileCoordinates::hash() const
{
    return _hash;
}



DynamicElementCoordinates TileCoordinates::toDynamicElementCoordinates() const
{
    return { static_cast<qreal>(_x), static_cast<qreal>(_y) };
}



int TileCoordinates::manhattanDistanceTo(const TileCoordinates& other) const
{
    return qAbs(_x - other._x) + qAbs(_y - other._y);
}



qreal TileCoordinates::chebyshevDistanceTo(const TileCoordinates& other) const
{
    return qMax(qFabs(_x - other._x), qFabs(_y - other._y));
}



qreal TileCoordinates::straightDistanceTo(const TileCoordinates& other) const
{
    const qreal X_DIFF(_x - other._x);
    const qreal Y_DIFF(_y - other._y);

    return qSqrt(X_DIFF * X_DIFF + Y_DIFF * Y_DIFF);
}



TileCoordinates::TileCoordinates() :
    _x(-1),
    _y(-1),
    _hash()
{

}



bool TileCoordinates::isValid() const
{
    return !_hash.isEmpty();
}
