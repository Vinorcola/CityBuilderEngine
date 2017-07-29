#include "CityEntryPoint.hpp"

CityEntryPoint::CityEntryPoint(const MapCoordinates& coordinates) :
    AbstractProcessableBuilding(MapArea(coordinates), coordinates)
{

}



void CityEntryPoint::process(const CycleDate& /*date*/)
{

}



void CityEntryPoint::processInteraction(const CycleDate& /*date*/, AbstractDynamicMapElement* /*actor*/)
{

}
