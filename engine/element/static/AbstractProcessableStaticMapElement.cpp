#include "AbstractProcessableStaticMapElement.hpp"



AbstractProcessableStaticMapElement::AbstractProcessableStaticMapElement(
    QObject* parent,
    const StaticElementInformation* conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    AbstractStaticMapElement(conf, area),
    AbstractProcessable(),
    entryPoint(entryPoint)
{

}



const MapCoordinates& AbstractProcessableStaticMapElement::getEntryPoint() const
{
    return entryPoint;
}
