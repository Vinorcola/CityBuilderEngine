#include "StaticElementAreaPartDescription.hpp"



StaticElementAreaPartDescription::StaticElementAreaPartDescription(QObject* parent, const MapCoordinates& anchorCoordinates, const MapSize& areaSize, Type type, int altitude) :
    QObject(parent),
    anchorCoordinates(anchorCoordinates),
    areaSize(areaSize),
    type(type),
    altitude(altitude)
{

}
