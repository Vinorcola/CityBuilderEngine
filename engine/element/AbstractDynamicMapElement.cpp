#include "AbstractDynamicMapElement.hpp"

#include <QDebug>



const qreal WALKER_SPEED(0.25); // 0.06





AbstractDynamicMapElement::AbstractDynamicMapElement(const MapCoordinates& initialLocation) :
    AbstractProcessable(),
    previousLocation(initialLocation),
    currentLocation(initialLocation),
    targetLocation(initialLocation)
{

}





const MapCoordinates& AbstractDynamicMapElement::getPreviousLocation() const
{
    return previousLocation;
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
            previousLocation = currentLocation;
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
        currentLocation.setX(qMin(currentLocation.getX() + WALKER_SPEED, targetLocation.getX()));
    }
    else if (targetLocation.getX() < currentLocation.getX())
    {
        currentLocation.setX(qMax(currentLocation.getX() - WALKER_SPEED, targetLocation.getX()));
    }

    if (targetLocation.getY() > currentLocation.getY())
    {
        currentLocation.setY(qMin(currentLocation.getY() + WALKER_SPEED, targetLocation.getY()));
    }
    else if (targetLocation.getY() < currentLocation.getY())
    {
        currentLocation.setY(qMax(currentLocation.getY() - WALKER_SPEED, targetLocation.getY()));
    }

    qDebug() << "  - Moved walker to" << currentLocation.toString();
}
