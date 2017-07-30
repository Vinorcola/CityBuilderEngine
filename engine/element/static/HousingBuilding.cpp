#include "HousingBuilding.hpp"

HousingBuilding::HousingBuilding(Map& map, const MapArea& area, const MapCoordinates& entryPoint, CityStatus& cityStatus, QWeakPointer<CityEntryPoint> cityEntryPoint) :
    AbstractProcessableStaticMapElement(area, entryPoint),
    map(map),
    cityStatus(cityStatus),
    cityEntryPoint(cityEntryPoint),
    housingCapacity(8),
    population(0)
{
    cityStatus.updateFreeHousingPlaces(housingCapacity);
}



void HousingBuilding::process(const CycleDate& /*date*/)
{

}



void HousingBuilding::processInteraction(const CycleDate& /*date*/, AbstractDynamicMapElement* /*actor*/)
{

}
