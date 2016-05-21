#include "MapCoordinates.hpp"

#include <QString>





MapCoordinates::MapCoordinates() :
    coordinates(-1, -1)
{

}





MapCoordinates::MapCoordinates(int x, int y) :
    coordinates(x, y)
{

}





MapCoordinates::MapCoordinates(qreal x, qreal y) :
    coordinates(x, y)
{

}





bool MapCoordinates::operator==(const MapCoordinates& other) const
{
    return coordinates.x() == other.coordinates.x() && coordinates.y() == other.coordinates.y();
}





bool MapCoordinates::operator!=(const MapCoordinates& other) const
{
    return coordinates.x() != other.coordinates.x() || coordinates.y() != other.coordinates.y();
}





bool MapCoordinates::isValid() const
{
    return coordinates.x() != -1 && coordinates.y() != -1;
}





int MapCoordinates::getX() const
{
    return coordinates.x();
}





int MapCoordinates::getY() const
{
    return coordinates.y();
}





QString MapCoordinates::toString() const
{
    return '(' + QString::number(coordinates.x()) + ';' + QString::number(coordinates.y()) + ')';
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
