#include "MotionHandler.hpp"

#include <cassert>

#include "src/engine/map/path/PathInterface.hpp"
#include "src/engine/random.hpp"
#include "src/exceptions/UnexpectedException.hpp"



MotionHandler::MotionHandler(const qreal speed, const MapCoordinates& initialLocation) :
    speed(speed),
    path(nullptr),
    location(initialLocation),
    movingFrom(initialLocation),
    movingTo()
{

}



MotionHandler::~MotionHandler()
{
    if (path) {
        delete path;
    }
}



const MapCoordinates& MotionHandler::getCurrentLocation() const
{
    return location;
}



MapCoordinates MotionHandler::getCurrentTileCoordinates() const
{
    return location.getRounded();
}



bool MotionHandler::isPathObsolete() const
{
    return path->isObsolete();
}



bool MotionHandler::isPathCompleted() const
{
    return path->isCompleted();
}



void MotionHandler::takePath(owner<PathInterface*> path)
{
    if (this->path) {
        delete this->path;
    }
    this->path = path;
    movingFrom = location;
    movingTo = path->getNextTargetCoordinates();
}



void MotionHandler::stop()
{
    if (path) {
        delete path;
        path = nullptr;
    }
    movingFrom = location;
    movingTo = {};
}



const MapCoordinates& MotionHandler::move()
{
    if (location == movingTo) {
        movingFrom = location;
        movingTo = path->getNextTargetCoordinates();
    }

    if (!movingTo.isValid()) {
        return location;
    }

    moveToTarget();

    return location;
}



void MotionHandler::moveToTarget()
{
    if (movingTo.getX() > location.getX()) {
        location.setX(qMin(location.getX() + speed, movingTo.getX()));
    }
    else if (movingTo.getX() < location.getX()) {
        location.setX(qMax(location.getX() - speed, movingTo.getX()));
    }

    if (movingTo.getY() > location.getY()) {
        location.setY(qMin(location.getY() + speed, movingTo.getY()));
    }
    else if (movingTo.getY() < location.getY()) {
        location.setY(qMax(location.getY() - speed, movingTo.getY()));
    }
}
