#include "AbstractDynamicMapElement.hpp"






AbstractDynamicMapElement::AbstractDynamicMapElement(const MapCoordinates& initialLocation) :
    AbstractProcessable(),
    currentLocation(initialLocation),
    targetLocation(),
    speed(0.25)
{

}





const MapCoordinates& AbstractDynamicMapElement::getCurrentLocation() const
{
    return currentLocation;
}





void AbstractDynamicMapElement::setNextTargetLocation(const MapCoordinates& nextLocation)
{
    targetLocation = nextLocation;
}





void AbstractDynamicMapElement::process()
{
    if (!targetLocation.isValid() || targetLocation == currentLocation)
    {
        targetLocation = getNextTargetLocation();
    }
}
