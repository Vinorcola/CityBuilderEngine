#include "Road.hpp"

#include <QDebug>



Road::Road(const StaticElementInformation* conf, const MapCoordinates& coordinates) :
    AbstractStaticMapElement(conf, MapArea(coordinates))
{
    qDebug() << "  - Created road at" << coordinates.toString();
}
