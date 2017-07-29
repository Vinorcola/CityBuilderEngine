#include "Road.hpp"

#include <QDebug>



Road::Road(const MapCoordinates& coordinates) :
    AbstractBuilding(MapArea(coordinates))
{
    qDebug() << "  - Created road at" << coordinates.toString();
}
