#include "AbstractDynamicMapElement.hpp"

#include <QDebug>



const qreal WALKER_SPEED(0.25); // 0.06



AbstractDynamicMapElement::AbstractDynamicMapElement(const MapCoordinates& initialLocation) :
    AbstractProcessable(),
    initialLocation(initialLocation),
    moveFromLocation(initialLocation),
    currentLocation(initialLocation),
    moveToLocation(initialLocation)
{

}



const MapCoordinates&AbstractDynamicMapElement::getInitialLocation() const
{
 return initialLocation;
}



const MapCoordinates& AbstractDynamicMapElement::getComingFromLocation() const
{
    return moveFromLocation;
}



const MapCoordinates& AbstractDynamicMapElement::getCurrentLocation() const
{
    return currentLocation;
}



const MapCoordinates& AbstractDynamicMapElement::getGoingToLocation() const
{
    return moveToLocation;
}



void AbstractDynamicMapElement::process(const CycleDate& /*date*/)
{
    if (moveToLocation.isValid()) {
        if (moveToLocation == currentLocation) {
            moveToLocation = findNextGoingToLocation();
            moveFromLocation = currentLocation;
            if (!moveToLocation.isValid()) {
                return;
            }
        }

        moveToTarget();
    }
}



void AbstractDynamicMapElement::moveToTarget()
{
    if (moveToLocation.getX() > currentLocation.getX()) {
        currentLocation.setX(qMin(currentLocation.getX() + WALKER_SPEED, moveToLocation.getX()));
    } else if (moveToLocation.getX() < currentLocation.getX()) {
        currentLocation.setX(qMax(currentLocation.getX() - WALKER_SPEED, moveToLocation.getX()));
    }
    if (moveToLocation.getY() > currentLocation.getY()) {
        currentLocation.setY(qMin(currentLocation.getY() + WALKER_SPEED, moveToLocation.getY()));
    } else if (moveToLocation.getY() < currentLocation.getY()) {
        currentLocation.setY(qMax(currentLocation.getY() - WALKER_SPEED, moveToLocation.getY()));
    }

    qDebug() << "  - Moved walker to" << currentLocation.toString();
}
