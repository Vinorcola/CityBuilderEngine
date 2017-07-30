#include "AbstractProcessableStaticMapElement.hpp"


AbstractProcessableStaticMapElement::AbstractProcessableStaticMapElement(const MapArea& area, const MapCoordinates& entryPoint) :
    AbstractStaticMapElement(area),
    AbstractProcessable(),
    entryPoint(entryPoint)
{

}


const MapCoordinates& AbstractProcessableStaticMapElement::getEntryPoint() const
{
    return entryPoint;
}
