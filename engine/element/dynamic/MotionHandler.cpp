#include "MotionHandler.hpp"

#include <cassert>

#include "engine/map/roadGraph/RoadGraphNode.hpp"
#include "engine/map/Map.hpp"
#include "engine/random.hpp"
#include "exceptions/UnexpectedException.hpp"



MotionHandler::MotionHandler(
    QObject* parent,
    const Map* map,
    qreal speed,
    const MapCoordinates& initialLocation,
    int wanderingCredits,
    bool restrictedToRoads
) :
    QObject(parent),
    map(map),
    speed(speed),
    restrictedToRoads(restrictedToRoads),
    isWanderingStrategy(wanderingCredits > 0),
    wanderingCredits(wanderingCredits),
    location(initialLocation),
    movingFrom(initialLocation),
    movingTo(),
    targetRoadNode(nullptr),
    target(),
    roadPath()
{
    if (isWanderingStrategy) {
        movingTo = getNextPathTile();
    }
}



void MotionHandler::setTarget(const RoadGraphNode* location)
{
    assert(location != nullptr);

    targetRoadNode = location;
    target = location->getCoordinates();
    calculatePath();
}



void MotionHandler::setTarget(const MapCoordinates& location)
{
    targetRoadNode = map->resolveRoad(location);
    target = location;
    calculatePath();
}



void MotionHandler::resetTarget()
{
    targetRoadNode = nullptr;
    target = MapCoordinates();
    calculatePath();
}



bool MotionHandler::hasReachedTarget() const
{
    return target.isValid() && location == target;
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
    if (movingTo.isValid()) {
        if (movingTo == location) {
            // Fetch next tile on the path.
            movingTo = getNextPathTile();
            movingFrom = location;
            if (!movingTo.isValid()) {
                return location;
            }
        }

        moveToTarget();
    }

    return location;
}



const RoadGraphNode* MotionHandler::getCurrentRoadNode() const
{
    auto roadNode(map->resolveRoad(location.getRounded()));
    if (!roadNode) {
        throw new UnexpectedException("Expected a road at location " + location.toString());
    }

    return roadNode;
}



void MotionHandler::calculatePath()
{
    if (!restrictedToRoads) {
        // Not implemented yet.
        assert(false);
    }

    movingFrom = location.getRounded();
    movingTo = MapCoordinates();
    roadPath.clear();
    if (!targetRoadNode) {
        return;
    }

    roadPath = map->getShortestRoadPathBetween(location, targetRoadNode->getCoordinates());
    if (roadPath.isEmpty()) {
        return;
    }

    if (roadPath.first()->getCoordinates() == location) {
        roadPath.takeFirst();
    }
    movingTo = getNextPathTile();
}



MapCoordinates MotionHandler::getNextPathTile()
{
    if (target.isValid()) {
        if (roadPath.empty()) {
            // Destination reached or no available path.
            return MapCoordinates();
        }

        return roadPath.takeFirst()->getCoordinates();
    }

    if (isWanderingStrategy) {
        // Use a wandering credit.
        --wanderingCredits;
        if (wanderingCredits == -1) {
            // Wandering credits expired.
            emit wanderingCreditsExpired();

            return movingTo; // During the emitted signal, a new target may be set and a movingTo location can already
                             // ba calculated, so we must not erase it. We return the current movingTo value.
        }

        return getNextRandomTile();
    }

    return MapCoordinates();
}



MapCoordinates MotionHandler::getNextRandomTile()
{
    auto neighbourNodes(getCurrentRoadNode()->getNeighbourNodeList());
    if (neighbourNodes.size() == 0) {
        // Character is on a single road tile.
        return MapCoordinates();
    }
    if (neighbourNodes.size() == 1) {
        // Dead end, must go back.
        return neighbourNodes.first()->getCoordinates();
    }
    // We remove the node we came from.
    for (auto node: neighbourNodes) {
        if (node->getCoordinates() == movingFrom) {
            neighbourNodes.removeOne(node);
            break;
        }
    }
    if (neighbourNodes.size() == 1) {
        // Only one choice left
        return neighbourNodes.first()->getCoordinates();
    }

    // Choose random.
    return neighbourNodes.at(randomInt(0, neighbourNodes.size() - 1))->getCoordinates();
}



void MotionHandler::moveToTarget()
{
    if (movingTo.getX() > location.getX()) {
        location.setX(qMin(location.getX() + speed, movingTo.getX()));
    } else if (movingTo.getX() < location.getX()) {
        location.setX(qMax(location.getX() - speed, movingTo.getX()));
    }
    if (movingTo.getY() > location.getY()) {
        location.setY(qMin(location.getY() + speed, movingTo.getY()));
    } else if (movingTo.getY() < location.getY()) {
        location.setY(qMax(location.getY() - speed, movingTo.getY()));
    }
}
