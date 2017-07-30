#include "CityEntryPoint.hpp"

CityEntryPoint::CityEntryPoint(QObject* parent, const MapCoordinates& coordinates) :
    AbstractProcessableStaticMapElement(parent, MapArea(coordinates), coordinates)
{

}



void CityEntryPoint::process(const CycleDate& /*date*/)
{

}



void CityEntryPoint::processInteraction(const CycleDate& /*date*/, AbstractDynamicMapElement* /*actor*/)
{

}
