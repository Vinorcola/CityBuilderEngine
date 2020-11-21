#include "MapCoordinates.hpp"

#include <QString>
#include <QtMath>

#include "src/exceptions/UnexpectedException.hpp"



MapCoordinates::MapCoordinates() :
    coordinates(-1, -1),
    hash()
{

}



MapCoordinates::MapCoordinates(const MapCoordinates& other) :
    coordinates(other.coordinates),
    hash(other.hash)
{

}



MapCoordinates::MapCoordinates(const int x, const int y) :
    coordinates(x, y),
    hash()
{

}



MapCoordinates::MapCoordinates(const qreal x, const qreal y) :
    coordinates(roundDecimal(x), roundDecimal(y)),
    hash()
{

}



void MapCoordinates::operator =(const MapCoordinates& other)
{
    coordinates = other.coordinates;
    hash = other.hash;
}



bool MapCoordinates::operator ==(const MapCoordinates& other) const
{
    return coordinates.x() == other.coordinates.x() && coordinates.y() == other.coordinates.y();
}



bool MapCoordinates::operator !=(const MapCoordinates& other) const
{
    return coordinates.x() != other.coordinates.x() || coordinates.y() != other.coordinates.y();
}



bool MapCoordinates::isValid() const
{
    return coordinates.x() != -1 || coordinates.y() != -1;
}



qreal MapCoordinates::getX() const
{
    return coordinates.x();
}



qreal MapCoordinates::getY() const
{
    return coordinates.y();
}



bool MapCoordinates::isRounded() const
{
    return qRound(coordinates.x()) == coordinates.x() && qRound(coordinates.y()) == coordinates.y();
}



void MapCoordinates::setX(const qreal x)
{
    coordinates.setX(roundDecimal(x));
}



void MapCoordinates::setY(const qreal y)
{
    coordinates.setY(roundDecimal(y));
}



MapCoordinates MapCoordinates::getNorth() const
{
    return { coordinates.x(), coordinates.y() - 1.0 };
}



MapCoordinates MapCoordinates::getSouth() const
{
    return { coordinates.x(), coordinates.y() + 1.0 };
}



MapCoordinates MapCoordinates::getEast() const
{
    return { coordinates.x() + 1.0, coordinates.y() };
}



MapCoordinates MapCoordinates::getWest() const
{
    return { coordinates.x() - 1.0, coordinates.y() };
}



MapCoordinates MapCoordinates::getTop() const
{
    return { coordinates.x() + 1.0, coordinates.y() - 1.0 };
}



MapCoordinates MapCoordinates::getRight() const
{
    return { coordinates.x() + 1.0, coordinates.y() + 1.0 };
}



MapCoordinates MapCoordinates::getBottom() const
{
    return { coordinates.x() - 1.0, coordinates.y() + 1.0 };
}



MapCoordinates MapCoordinates::getLeft() const
{
    return { coordinates.x() - 1.0, coordinates.y() - 1.0 };
}



MapCoordinates MapCoordinates::getRounded() const
{
    return { qRound(coordinates.x()), qRound(coordinates.y()) };
}



QList<MapCoordinates> MapCoordinates::getClosestRounded() const
{
    if (isRounded()) {
        return { *this };
    }

    MapCoordinates rounded(getRounded());
    if (coordinates.x() > rounded.coordinates.x()) {
        // East.
        return { rounded, rounded.getEast() };
    }
    if (coordinates.x() < rounded.coordinates.x()) {
        // West.
        return { rounded, rounded.getWest() };
    }
    if (coordinates.y() > rounded.coordinates.y()) {
        // South.
        return { rounded, rounded.getSouth() };
    }
    if (coordinates.y() < rounded.coordinates.y()) {
        // North.
        return { rounded, rounded.getNorth() };
    }

    throw new UnexpectedException("Unexpected behavior in MapCoordinates::getClosestRounded().");
}



qreal MapCoordinates::getManhattanDistanceTo(const MapCoordinates& other) const
{
    return qFabs(coordinates.x() - other.coordinates.x()) + qFabs(coordinates.y() - other.coordinates.y());
}



qreal MapCoordinates::getChebyshevDistanceTo(const MapCoordinates& other) const
{
    return qMax(qFabs(coordinates.x() - other.coordinates.x()), qFabs(coordinates.y() - other.coordinates.y()));
}



qreal MapCoordinates::getStraightDistanceTo(const MapCoordinates& other) const
{
    qreal xDiff(coordinates.x() - other.coordinates.x());
    qreal yDiff(coordinates.y() - other.coordinates.y());

    return qSqrt(xDiff * xDiff + yDiff * yDiff);
}



QString MapCoordinates::getHash() const
{
    if (hash.isEmpty()) {
        // Cache the value to avoid calculating it each time.
        const_cast<MapCoordinates*>(this)->hash = QString::number(coordinates.x()) + ';' + QString::number(coordinates.y());
    }

    return hash;
}



QString MapCoordinates::toString() const
{
    return '(' + QString::number(coordinates.x()) + ';' + QString::number(coordinates.y()) + ')';
}



qreal MapCoordinates::roundDecimal(qreal coordinate) const
{
    return qRound(1000.0 * coordinate) / 1000.0;
}
