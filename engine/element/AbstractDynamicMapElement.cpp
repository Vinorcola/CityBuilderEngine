#include "AbstractDynamicMapElement.hpp"

#include <QDebug>



const qreal WALKER_SPEED(0.25);





AbstractDynamicMapElement::AbstractDynamicMapElement(const MapCoordinates& initialLocation) :
    AbstractProcessable(),
    currentLocation(initialLocation),
    targetLocation(initialLocation)
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





void AbstractDynamicMapElement::process(const CycleDate& /*date*/)
{
    if (targetLocation.isValid())
    {
        if (targetLocation == currentLocation)
        {
            targetLocation = getNextTargetLocation();
            if (!targetLocation.isValid())
            {
                return;
            }
        }

        moveToTarget();
    }
}





void AbstractDynamicMapElement::moveToTarget()
{
    if (targetLocation.getX() > currentLocation.getX())
    {
        currentLocation.setX(currentLocation.getX() + WALKER_SPEED);
    }
    else if (targetLocation.getX() < currentLocation.getX())
    {
        currentLocation.setX(currentLocation.getX() + WALKER_SPEED);
    }

    if (targetLocation.getY() > currentLocation.getY())
    {
        currentLocation.setY(currentLocation.getY() + WALKER_SPEED);
    }
    else if (targetLocation.getY() < currentLocation.getY())
    {
        currentLocation.setY(currentLocation.getY() + WALKER_SPEED);
    }

    qDebug() << "Moved walker to" << currentLocation.toString();
}
