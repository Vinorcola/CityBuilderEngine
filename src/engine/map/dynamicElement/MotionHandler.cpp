#include "MotionHandler.hpp"

#include <QtCore/QtMath>

#include "src/engine/map/path/PathInterface.hpp"
#include "src/engine/map/Tile.hpp"



MotionHandler::MotionHandler(const qreal speed, const Tile& initialTile) :
    speed(speed),
    path(),
    location(initialTile.coordinates().toDynamicElementCoordinates()),
    movingFrom(&initialTile),
    movingTo(nullptr),
    direction(Direction::West)
{

}



const DynamicElementCoordinates& MotionHandler::getCurrentLocation() const
{
    return location;
}



const Tile& MotionHandler::getCurrentTile() const
{
    return movingTo ? *movingTo : *movingFrom;
}



Direction MotionHandler::getCurrentDirection() const
{
    return direction;
}



bool MotionHandler::isPathObsolete() const
{
    return !path.isNull() && path->isObsolete();
}



bool MotionHandler::isPathCompleted() const
{
    return !path.isNull() && path->isCompleted() && location == movingTo->coordinates().toDynamicElementCoordinates();
}



void MotionHandler::takePath(QSharedPointer<PathInterface> path)
{
    this->path = path;
    movingTo = nullptr;
    if (path->isNextTileValid()) {
        movingTo = &path->getNextTile();
        if (movingTo == movingFrom) {
            // Some path may include the current location as the first step, we switch directly to the next step.
            if (path->isNextTileValid()) {
                movingTo = &path->getNextTile();
            }
        }
        updateDirection();
    }
}



bool MotionHandler::move()
{
    if (path.isNull()) {
        return false;
    }

    if (!movingTo) {
        return false;
    }

    if (location == movingTo->coordinates().toDynamicElementCoordinates()) {
        movingFrom = movingTo;
        movingTo = nullptr;
        if (path->isNextTileValid()) {
            movingTo = &path->getNextTile();
        }
        updateDirection();
    }

    if (!movingTo) {
        return false;
    }

    return moveToTarget();
}



bool MotionHandler::moveToTarget()
{
    bool hasMoved(false);
    auto& movingToCoordinates(movingTo->coordinates());
    if (movingToCoordinates.x() > location.x()) {
        location = { qMin(location.x() + speed, static_cast<qreal>(movingToCoordinates.x())), location.y() };
        hasMoved = true;
    }
    else if (movingToCoordinates.x() < location.x()) {
        location = { qMax(location.x() - speed, static_cast<qreal>(movingToCoordinates.x())), location.y() };
        hasMoved = true;
    }

    if (movingToCoordinates.y() > location.y()) {
        location = { location.x(), qMin(location.y() + speed, static_cast<qreal>(movingToCoordinates.y())) };
        hasMoved = true;
    }
    else if (movingToCoordinates.y() < location.y()) {
        location = { location.x(), qMax(location.y() - speed, static_cast<qreal>(movingToCoordinates.y())) };
        hasMoved = true;
    }

    return hasMoved;
}



void MotionHandler::updateDirection()
{
    if (!movingTo) {
        return;
    }

    if (movingFrom->coordinates().x() < movingTo->coordinates().x()) {
        if (movingFrom->coordinates().y() < movingTo->coordinates().y()) {
            direction = Direction::Right;
        }
        else if (movingFrom->coordinates().y() == movingTo->coordinates().y()) {
            direction = Direction::East;
        }
        else {
            direction = Direction::Top;
        }
    }
    else if (movingFrom->coordinates().x() == movingTo->coordinates().x()) {

        if (movingFrom->coordinates().y() < movingTo->coordinates().y()) {
            direction = Direction::South;
        }
        else {
            direction = Direction::North;
        }
    }
    else {
        if (movingFrom->coordinates().y() < movingTo->coordinates().y()) {
            direction = Direction::Bottom;
        }
        else if (movingFrom->coordinates().y() == movingTo->coordinates().y()) {
            direction = Direction::West;
        }
        else {
            direction = Direction::Left;
        }
    }
}
