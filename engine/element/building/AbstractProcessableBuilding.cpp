#include "AbstractProcessableBuilding.hpp"


AbstractProcessableBuilding::AbstractProcessableBuilding(const MapArea& area, const MapCoordinates& entryPoint) :
    AbstractBuilding(area),
    AbstractProcessable(),
    entryPoint(entryPoint)
{

}


const MapCoordinates& AbstractProcessableBuilding::getEntryPoint() const
{
    return entryPoint;
}
