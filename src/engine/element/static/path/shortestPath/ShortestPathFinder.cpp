#include "ShortestPathFinder.hpp"

#include <cmath>
#include <QtCore/QHash>

#include "src/engine/element/static/path/shortestPath/AStarNode.hpp"
#include "src/engine/element/static/path/shortestPath/ProcessedAStarNodeList.hpp"
#include "src/engine/element/static/path/shortestPath/UnprocessedAStarNodeList.hpp"
#include "src/engine/element/static/path/MapDetailsInterface.hpp"

const qreal DIAGONAL_LENGTH(sqrt(2.0));



ShortestPathFinder::ShortestPathFinder(const MapDetailsInterface& mapDetails) :
    mapDetails(mapDetails)
{

}



QList<MapCoordinates> ShortestPathFinder::getShortestPath(
    const MapCoordinates& origin,
    const MapCoordinates& destination,
    const bool restrictedToRoads
) const {

    QList<MapCoordinates> path;
    ProcessedAStarNodeList closedPathNodes;
    UnprocessedAStarNodeList openedPathNodes;
    QHash<AStarNode*, AStarNode*> parents;

    // Initialize.
    if (origin.isRounded()) {
        openedPathNodes.insertNodeToProcess(new AStarNode(origin, destination, 0.0, !restrictedToRoads));
    }
    else {
        // We get here the both nodes around the origin coordinates and initialize them with cost according to origin.
        for (auto originRoundedCoordinates : origin.getClosestRounded()) {
            openedPathNodes.insertNodeToProcess(new AStarNode(
                originRoundedCoordinates,
                destination,
                originRoundedCoordinates.getManhattanDistanceTo(origin),
                !restrictedToRoads
            ));
        }
    }

    while (openedPathNodes.hasNodeToProcess()) {
        auto current(openedPathNodes.takeClosestToDestination());
        closedPathNodes.markNodeAsProcessed(current);

        if (current->isDestination()) {
            while (current) {
                path.prepend(current->getLocation());
                current = parents.value(current);
            }
            break;
        }

        qreal neighboursCostFromOrigin(current->getCostFromOrigin() + 1.0);
        for (auto neighbourLocation : current->getNeighbours()) {
            if (closedPathNodes.isNodeForLocationAlreadyProcessed(neighbourLocation)) {
                continue;
            }
            if (!mapDetails.isLocationTraversable(neighbourLocation)) {
                continue;
            }
            if (restrictedToRoads && !mapDetails.hasRoadAtLocation(neighbourLocation)) {
                continue;
            }

            auto neighbour(openedPathNodes.findClosestToDestinationAtLocation(neighbourLocation));
            if (neighbour) {
                if (neighboursCostFromOrigin < neighbour->getCostFromOrigin()) {
                    // Update the existing neighbour cost.
                    parents[neighbour] = current;
                    neighbour->updateCostIfBetter(neighboursCostFromOrigin);
                }
            }
            else {
                // Create neighbour node and insert it in the opened path nodes.
                neighbour = new AStarNode(neighbourLocation, destination, neighboursCostFromOrigin, !restrictedToRoads);
                parents[neighbour] = current;
                openedPathNodes.insertNodeToProcess(neighbour);
            }
        }

        if (!restrictedToRoads) {
            neighboursCostFromOrigin = current->getCostFromOrigin() + DIAGONAL_LENGTH;
            for (auto neighbourLocation : current->getDiagonalNeighbours()) {
                if (closedPathNodes.isNodeForLocationAlreadyProcessed(neighbourLocation)) {
                    continue;
                }
                if (!mapDetails.isLocationTraversable(neighbourLocation)) {
                    continue;
                }
                if (restrictedToRoads && !mapDetails.hasRoadAtLocation(neighbourLocation)) {
                    continue;
                }

                auto neighbour(openedPathNodes.findClosestToDestinationAtLocation(neighbourLocation));
                if (neighbour) {
                    if (neighboursCostFromOrigin < neighbour->getCostFromOrigin()) {
                        // Update the existing neighbour cost.
                        parents[neighbour] = current;
                        neighbour->updateCostIfBetter(neighboursCostFromOrigin);
                    }
                }
                else {
                    // Create neighbour node and insert it in the opened path nodes.
                    neighbour = new AStarNode(neighbourLocation, destination, neighboursCostFromOrigin, !restrictedToRoads);
                    parents[neighbour] = current;
                    openedPathNodes.insertNodeToProcess(neighbour);
                }
            }
        }
    }

    return path;
}



QList<MapCoordinates> ShortestPathFinder::getShortestRoadablePath(
    const MapCoordinates& origin,
    const MapCoordinates& destination
) const {

    QList<MapCoordinates> path;
    ProcessedAStarNodeList closedPathNodes;
    UnprocessedAStarNodeList openedPathNodes;
    QHash<AStarNode*, AStarNode*> parents;

    // Initialize.
    openedPathNodes.insertNodeToProcess(new AStarNode(origin, destination, 0.0, false));

    while (openedPathNodes.hasNodeToProcess()) {
        auto current(openedPathNodes.takeClosestToDestination());
        closedPathNodes.markNodeAsProcessed(current);

        if (current->isDestination()) {
            while (current) {
                path.prepend(current->getLocation());
                current = parents.value(current);
            }
            break;
        }

        qreal neighboursCostFromOrigin(current->getCostFromOrigin() + 1.0);
        for (auto neighbourLocation : current->getNeighbours()) {
            if (closedPathNodes.isNodeForLocationAlreadyProcessed(neighbourLocation)) {
                continue;
            }
            if (!mapDetails.canConstructRoadAtLocation(neighbourLocation)) {
                continue;
            }

            auto neighbour(openedPathNodes.findClosestToDestinationAtLocation(neighbourLocation));
            if (neighbour) {
                if (neighboursCostFromOrigin < neighbour->getCostFromOrigin()) {
                    // Update the existing neighbour cost.
                    parents[neighbour] = current;
                    neighbour->updateCostIfBetter(neighboursCostFromOrigin);
                }
            }
            else {
                // Create neighbour node and insert it in the opened path nodes.
                neighbour = new AStarNode(neighbourLocation, destination, neighboursCostFromOrigin, false);
                parents[neighbour] = current;
                openedPathNodes.insertNodeToProcess(neighbour);
            }
        }
    }

    return path;
}