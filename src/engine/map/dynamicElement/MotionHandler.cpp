#include "MotionHandler.hpp"

#include <QtCore/QtMath>

#include "src/engine/map/path/PathInterface.hpp"



MotionHandler::MotionHandler(const qreal speed, const DynamicElementCoordinates& initialLocation) :
    speed(speed),
    path(),
    location(initialLocation),
    movingFrom(initialLocation.associatedTileCoordinates()),
    movingTo(initialLocation.associatedTileCoordinates()),
    direction(Direction::West)
{

}



const DynamicElementCoordinates& MotionHandler::getCurrentLocation() const
{
    return location;
}



Direction MotionHandler::getCurrentDirection() const
{
    return direction;
}



TileCoordinates MotionHandler::getCurrentTileCoordinates() const
{
    return location.associatedTileCoordinates();
}



bool MotionHandler::isPathObsolete() const
{
    return !path.isNull() && path->isObsolete();
}



bool MotionHandler::isPathCompleted() const
{
    return !path.isNull() && path->isCompleted() && location == movingTo.toDynamicElementCoordinates();
}



void MotionHandler::takePath(QSharedPointer<PathInterface> path)
{
    this->path = path;
    movingFrom = location.associatedTileCoordinates();
    if (path->isNextTargetCoordinatesValid()) {
        movingTo = path->getNextValidTargetCoordinates();
        if (movingTo == movingFrom) {
            // Some path may include the current location as the first step, we switch directly to the next step.
            if (path->isNextTargetCoordinatesValid()) {
                movingTo = path->getNextValidTargetCoordinates();
            }
            else {
                movingTo = movingFrom;
            }
        }
    }
    else {
        movingTo = movingFrom;
    }
    updateDirection();
}



void MotionHandler::stop()
{
    path.reset();
    movingFrom = location.associatedTileCoordinates();
    movingTo = location.associatedTileCoordinates();
}



bool MotionHandler::move()
{
    if (path.isNull()) {
        return false;
    }

    if (location == movingTo.toDynamicElementCoordinates()) {
        // We use `movingTo` rather than `location` to set the coordinates of `movingFrom`, because `movingTo` is sure
        // to be rounded coordinates when `location` is not.
        movingFrom = movingTo;
        if (path->isNextTargetCoordinatesValid()) {
            movingTo = path->getNextValidTargetCoordinates();
        }
        else {
            movingTo = movingFrom;
        }
        updateDirection();
    }

    if (movingTo == movingFrom) {
        return false;
    }

    return moveToTarget();
}



bool MotionHandler::moveToTarget()
{
    bool hasMoved(false);
    if (movingTo.x() > location.x()) {
        location = { qMin(location.x() + speed, static_cast<qreal>(movingTo.x())), location.y() };
        hasMoved = true;
    }
    else if (movingTo.x() < location.x()) {
        location = { qMax(location.x() - speed, static_cast<qreal>(movingTo.x())), location.y() };
        hasMoved = true;
    }

    if (movingTo.y() > location.y()) {
        location = { location.x(), qMin(location.y() + speed, static_cast<qreal>(movingTo.y())) };
        hasMoved = true;
    }
    else if (movingTo.y() < location.y()) {
        location = { location.x(), qMax(location.y() - speed, static_cast<qreal>(movingTo.y())) };
        hasMoved = true;
    }

    return hasMoved;
}



void MotionHandler::updateDirection()
{
    // TODO: To correct
    direction = Direction::West;
    /*
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
    }*/
}
