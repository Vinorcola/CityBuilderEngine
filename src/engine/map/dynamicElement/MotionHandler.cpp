#include "MotionHandler.hpp"

#include "src/engine/map/path/PathInterface.hpp"
#include "src/exceptions/UnexpectedException.hpp"



MotionHandler::MotionHandler(const qreal speed, const MapCoordinates& initialLocation) :
    speed(speed),
    path(nullptr),
    location(initialLocation),
    movingFrom(initialLocation),
    movingTo(),
    direction(Direction::West)
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



Direction MotionHandler::getCurrentDirection() const
{
    return direction;
}



MapCoordinates MotionHandler::getCurrentTileCoordinates() const
{
    return location.getRounded();
}



bool MotionHandler::isPathObsolete() const
{
    return path != nullptr && path->isObsolete();
}



bool MotionHandler::isPathCompleted() const
{
    return path != nullptr && path->isCompleted() && location == movingTo;
}



void MotionHandler::takePath(owner<PathInterface*> path)
{
    if (this->path) {
        delete this->path;
    }
    this->path = path;
    movingFrom = location;
    movingTo = path->getNextTargetCoordinates();
    if (movingTo == movingFrom) {
        // Some path may include the current location as the first step, we switch directly to the next step.
        movingTo = path->getNextTargetCoordinates();
    }
    updateDirection();
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



bool MotionHandler::move()
{
    if (location == movingTo) {
        // We use `movingTo` rather than `location` to set the coordinates of `movingFrom`, because `movingTo` is sure
        // to be rounded coordinates when `location` is not.
        movingFrom = movingTo;
        movingTo = path->getNextTargetCoordinates();
        updateDirection();
    }

    if (!movingTo.isValid()) {
        return false;
    }

    return moveToTarget();
}



bool MotionHandler::moveToTarget()
{
    bool hasMoved(false);
    if (movingTo.getX() > location.getX()) {
        location.setX(qMin(location.getX() + speed, movingTo.getX()));
        hasMoved = true;
    }
    else if (movingTo.getX() < location.getX()) {
        location.setX(qMax(location.getX() - speed, movingTo.getX()));
        hasMoved = true;
    }

    if (movingTo.getY() > location.getY()) {
        location.setY(qMin(location.getY() + speed, movingTo.getY()));
        hasMoved = true;
    }
    else if (movingTo.getY() < location.getY()) {
        location.setY(qMax(location.getY() - speed, movingTo.getY()));
        hasMoved = true;
    }

    return hasMoved;
}



void MotionHandler::updateDirection()
{
    if (movingFrom.getTop() == movingTo) {
        direction = Direction::Top;
    }
    else if (movingFrom.getRight() == movingTo) {
        direction = Direction::Right;
    }
    else if (movingFrom.getBottom() == movingTo) {
        direction = Direction::Bottom;
    }
    else if (movingFrom.getLeft() == movingTo) {
        direction = Direction::Left;
    }
    else if (movingFrom.getNorth() == movingTo) {
        direction = Direction::North;
    }
    else if (movingFrom.getEast() == movingTo) {
        direction = Direction::East;
    }
    else if (movingFrom.getSouth() == movingTo) {
        direction = Direction::South;
    }
    else if (movingFrom.getWest() == movingTo) {
        direction = Direction::West;
    }
}
