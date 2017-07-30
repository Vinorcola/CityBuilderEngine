#include "AbstractDynamicMapElement.hpp"

#include <QDebug>

#include "defines.hpp"



AbstractDynamicMapElement::AbstractDynamicMapElement(QWeakPointer<AbstractProcessableStaticMapElement> issuer, const qreal speed) :
    AbstractProcessable(),
    initialLocation(issuer.toStrongRef()->getEntryPoint()),
    moveFromLocation(initialLocation),
    currentLocation(initialLocation),
    moveToLocation(initialLocation),
    speed(speed),
    issuer(issuer)
{

}



AbstractDynamicMapElement::~AbstractDynamicMapElement()
{

}



const MapCoordinates& AbstractDynamicMapElement::getInitialLocation() const
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



void AbstractDynamicMapElement::process(const CycleDate& date)
{
    if (moveToLocation.isValid()) {
        if (moveToLocation == currentLocation) {
            moveToLocation = findNextGoingToLocation(date);
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
        currentLocation.setX(qMin(currentLocation.getX() + speed, moveToLocation.getX()));
    } else if (moveToLocation.getX() < currentLocation.getX()) {
        currentLocation.setX(qMax(currentLocation.getX() - speed, moveToLocation.getX()));
    }
    if (moveToLocation.getY() > currentLocation.getY()) {
        currentLocation.setY(qMin(currentLocation.getY() + speed, moveToLocation.getY()));
    } else if (moveToLocation.getY() < currentLocation.getY()) {
        currentLocation.setY(qMax(currentLocation.getY() - speed, moveToLocation.getY()));
    }

    qDebug() << "  - Moved walker to" << currentLocation.toString();
}
