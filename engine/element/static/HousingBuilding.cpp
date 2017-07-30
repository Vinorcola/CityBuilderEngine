#include "HousingBuilding.hpp"

HousingBuilding::HousingBuilding(QObject* parent, const MapArea& area, const MapCoordinates& entryPoint) :
    AbstractProcessableStaticMapElement(parent, area, entryPoint),
    housingCapacity(8),
    population(0)
{

}



void HousingBuilding::process(const CycleDate& /*date*/)
{

}



void HousingBuilding::processInteraction(const CycleDate& /*date*/, AbstractDynamicMapElement* /*actor*/)
{

}
