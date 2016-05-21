#include "AbstractMovableElement.hpp"





AbstractMovableElement::AbstractMovableElement(Map& map, const MapCoordinates& initialLocation) :
    AbstractMapElement(map),
    AbstractProcessable(map.getProcessor()),
    currentLocation(initialLocation),
    targetLocation()
{

}





const MapCoordinates& AbstractMovableElement::getCurrentLocation() const
{
    return currentLocation;
}





void AbstractMovableElement::setNextTargetLocation(const MapCoordinates& nextLocation)
{
    targetLocation = nextLocation;
}





void AbstractMovableElement::process()
{
    if (!targetLocation.isValid() || targetLocation == currentLocation)
    {
        targetLocation = getNextTargetLocation();
    }
}
