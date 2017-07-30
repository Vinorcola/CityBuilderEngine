#include "CityEntryPoint.hpp"

CityEntryPoint::CityEntryPoint(const MapCoordinates& coordinates) :
    AbstractProcessableStaticMapElement(MapArea(coordinates), coordinates)
{

}



void CityEntryPoint::process(const CycleDate& /*date*/)
{

}



void CityEntryPoint::processInteraction(const CycleDate& /*date*/, AbstractDynamicMapElement* /*actor*/)
{

}
