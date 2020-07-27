#include "PathFinder.hpp"

#include <QtCore/QHash>

#include "src/engine/map/path/MapDetailsInterface.hpp"
#include "src/engine/map/path/aStar/AStarNode.hpp"
#include "src/engine/map/path/aStar/ProcessedAStarNodeList.hpp"
#include "src/engine/map/path/aStar/UnprocessedAStarNodeList.hpp"



PathFinder::PathFinder(const MapDetailsInterface& mapDetails) :
    mapDetails(mapDetails)
{

}



QList<MapCoordinates> PathFinder::getShortestPath(
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
            if (restrictedToRoads && !mapDetails.isLocationARoad(neighbourLocation)) {
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

    return path;
}
