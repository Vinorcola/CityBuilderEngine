#include "AbstractProcessableStaticMapElement.hpp"


AbstractProcessableStaticMapElement::AbstractProcessableStaticMapElement(QObject* parent, const MapArea& area, const MapCoordinates& entryPoint) :
    AbstractProcessable(parent),
    AbstractStaticMapElement(area),
    entryPoint(entryPoint)
{

}


const MapCoordinates& AbstractProcessableStaticMapElement::getEntryPoint() const
{
    return entryPoint;
}
