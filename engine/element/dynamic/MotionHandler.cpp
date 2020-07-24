#include "MotionHandler.hpp"

#include <cassert>

#include "engine/map/roadGraph/RoadGraphNode.hpp"
#include "engine/map/Map.hpp"
#include "engine/random.hpp"
#include "exceptions/UnexpectedException.hpp"



MotionHandler::MotionHandler(QObject* parent,
    const Map* map,
    qreal speed,
    const MapCoordinates& initialLocation,
    int randomWalkingCredit,
    bool restrictedToRoads
) :
    QObject(parent),
    map(map),
    speed(speed),
    restrictedToRoads(restrictedToRoads),
    randomWalker(randomWalkingCredit > 0),
    randomWalkingCredit(randomWalkingCredit),
    location(initialLocation),
    moveFrom(initialLocation),
    moveTo(),
    targetRoadNode(nullptr),
    target(),
    roadPath()
{
    if (randomWalker) {
        moveTo = getNextPathTile();
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
    if (moveTo.isValid()) {
        if (moveTo == location) {
            // Fetch next tile on the path.
            moveTo = getNextPathTile();
            moveFrom = location;
            if (!moveTo.isValid()) {
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

    moveFrom = location.getRounded();
    moveTo = MapCoordinates();
    roadPath.clear();
    if (!targetRoadNode) {
        return;
    }

    roadPath = map->getShortestRoadPathBetween(location, targetRoadNode->getCoordinates());
    if (!roadPath.isEmpty()) {
        if (roadPath.first()->getCoordinates() == location) {
            roadPath.takeFirst();
        }
        moveTo = getNextPathTile();
    }
}



MapCoordinates MotionHandler::getNextPathTile()
{
    // As soon as a character has a valid target, it becomes a targeted walker, even if it was a random walker that
    // still has some walking credit.
    if (target.isValid()) {
        if (roadPath.empty()) {
            // Destination reached or no path available.
            return MapCoordinates();
        }

        return roadPath.takeFirst()->getCoordinates();
    }

    // Random walker.
    if (randomWalker) {
        // Update walking credit
        --randomWalkingCredit;
        if (randomWalkingCredit == -1) {
            // Walking credit expires.
            emit walkingCreditExpired();

            return moveTo;
        }

        return getNextRandomTile();
    }

    return MapCoordinates();
}



MapCoordinates MotionHandler::getNextRandomTile()
{
    // Continue random walking.
    auto neighbourNodes(getCurrentRoadNode()->getNeighbourNodeList());
    if (neighbourNodes.size() == 0) {
        // Character is on a single road tile.
        return MapCoordinates();
    }
    if (neighbourNodes.size() == 1) {
        // Dead end, must go back.
        return neighbourNodes.first()->getCoordinates();
    }
    // Remove the node we come from.
    for (auto node: neighbourNodes) {
        if (node->getCoordinates() == moveFrom) {
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
    if (moveTo.getX() > location.getX()) {
        location.setX(qMin(location.getX() + speed, moveTo.getX()));
    } else if (moveTo.getX() < location.getX()) {
        location.setX(qMax(location.getX() - speed, moveTo.getX()));
    }
    if (moveTo.getY() > location.getY()) {
        location.setY(qMin(location.getY() + speed, moveTo.getY()));
    } else if (moveTo.getY() < location.getY()) {
        location.setY(qMax(location.getY() - speed, moveTo.getY()));
    }
}
