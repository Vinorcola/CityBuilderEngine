#include "AbstractProcessableStaticMapElement.hpp"



AbstractProcessableStaticMapElement::AbstractProcessableStaticMapElement(
    QObject* parent,
    const StaticElementInformation* conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    AbstractProcessable(parent),
    AbstractStaticMapElement(conf, area),
    entryPoint(entryPoint)
{

}



const MapCoordinates& AbstractProcessableStaticMapElement::getEntryPoint() const
{
    return entryPoint;
}
