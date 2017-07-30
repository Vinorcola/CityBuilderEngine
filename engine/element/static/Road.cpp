#include "Road.hpp"

#include <QDebug>



Road::Road(const MapCoordinates& coordinates) :
    AbstractStaticMapElement(MapArea(coordinates))
{
    qDebug() << "  - Created road at" << coordinates.toString();
}
