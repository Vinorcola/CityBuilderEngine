#include "StaticElementAreaPartDescription.hpp"





StaticElementAreaPartDescription::StaticElementAreaPartDescription(const MapCoordinates& anchorCoordinates, const MapSize& areaSize, Type type, int altitude) :
    anchorCoordinates(anchorCoordinates),
    areaSize(areaSize),
    type(type),
    altitude(altitude)
{

}
