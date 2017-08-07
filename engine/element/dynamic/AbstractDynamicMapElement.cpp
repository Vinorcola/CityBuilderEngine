#include "AbstractDynamicMapElement.hpp"

#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"



AbstractDynamicMapElement::AbstractDynamicMapElement(QObject* parent, const DynamicElementInformation* conf, AbstractProcessableStaticMapElement* issuer) :
    AbstractProcessable(parent),
    AbstractMapElement(),
    conf(conf),
    initialLocation(issuer->getEntryPoint()),
    moveFromLocation(initialLocation),
    currentLocation(initialLocation),
    moveToLocation(initialLocation),
    issuer(issuer)
{

}



const DynamicElementInformation* AbstractDynamicMapElement::getConf() const
{
    return conf;
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



AbstractProcessableStaticMapElement* AbstractDynamicMapElement::getIssuer() const
{
    return issuer;
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
        currentLocation.setX(qMin(currentLocation.getX() + conf->getSpeed(), moveToLocation.getX()));
    } else if (moveToLocation.getX() < currentLocation.getX()) {
        currentLocation.setX(qMax(currentLocation.getX() - conf->getSpeed(), moveToLocation.getX()));
    }
    if (moveToLocation.getY() > currentLocation.getY()) {
        currentLocation.setY(qMin(currentLocation.getY() + conf->getSpeed(), moveToLocation.getY()));
    } else if (moveToLocation.getY() < currentLocation.getY()) {
        currentLocation.setY(qMax(currentLocation.getY() - conf->getSpeed(), moveToLocation.getY()));
    }
}
