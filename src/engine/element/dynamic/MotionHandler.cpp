#include "MotionHandler.hpp"

#include <cassert>

#include "src/engine/map/path/PathGenerator.hpp"
#include "src/engine/map/path/PathInterface.hpp"
#include "src/engine/map/roadGraph/RoadGraphNode.hpp"
#include "src/engine/random.hpp"
#include "src/exceptions/UnexpectedException.hpp"



MotionHandler::MotionHandler(
    QObject* parent,
    const PathGenerator& pathGenerator,
    qreal speed,
    const MapCoordinates& initialLocation,
    int wanderingCredits
) :
    QObject(parent),
    pathGenerator(pathGenerator),
    speed(speed),
    restrictedToRoads(true),
    destination(),
    path(pathGenerator.generateWanderingPath(initialLocation, wanderingCredits)),
    location(initialLocation),
    movingFrom(initialLocation),
    movingTo(path->getNextTargetCoordinates())
{

}



MotionHandler::MotionHandler(QObject* parent,
    const PathGenerator& pathGenerator,
    qreal speed,
    const MapCoordinates& initialLocation,
    const MapCoordinates& destination,
    bool restrictedToRoads
) :
    QObject(parent),
    pathGenerator(pathGenerator),
    speed(speed),
    restrictedToRoads(restrictedToRoads),
    destination(destination),
    path(
        restrictedToRoads ?
            pathGenerator.generateShortestRoadPathTo(initialLocation, destination) :
            pathGenerator.generateShortestPathTo(initialLocation, destination)
    ),
    location(initialLocation),
    movingFrom(initialLocation),
    movingTo(path->getNextTargetCoordinates())
{

}



MotionHandler::~MotionHandler()
{
    if (path) {
        delete path;
    }
}



void MotionHandler::changeDestination(const RoadGraphNode* location)
{
    assert(location != nullptr);

    changeDestination(location->getCoordinates());
}



void MotionHandler::changeDestination(const MapCoordinates& destination)
{
    this->destination = destination;
    if (path) {
        delete path;
    }
    path = restrictedToRoads ?
        pathGenerator.generateShortestRoadPathTo(location, destination) :
        pathGenerator.generateShortestPathTo(location, destination);
    movingFrom = location;
    movingTo = path->getNextTargetCoordinates();
}



void MotionHandler::resetDestination()
{
    destination = MapCoordinates();
    if (path) {
        delete path;
        path = nullptr;
    }
    movingFrom = location;
    movingTo = MapCoordinates();
}



bool MotionHandler::isPathCompleted() const
{
    return !movingTo.isValid() && (!destination.isValid() || location == destination);
}



bool MotionHandler::isWanderingMotion() const
{
    return !destination.isValid();
}



const MapCoordinates& MotionHandler::getCurrentLocation() const
{
    return location;
}



MapCoordinates MotionHandler::getCurrentTileCoordinates() const
{
    return location.getRounded();
}



const MapCoordinates& MotionHandler::move()
{
    if (location == movingTo) {
        configureNextMovingStep();
    }

    if (!movingTo.isValid()) {
        return location;
    }

    moveToTarget();

    return location;
}



void MotionHandler::configureNextMovingStep()
{
    movingFrom = location;
    movingTo = path->getNextTargetCoordinates();
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
