#include "ClosestPathFinder.hpp"

#include <cmath>
#include <QtCore/QHash>

#include "src/engine/element/static/path/closestPath/PathNode.hpp"
#include "src/engine/element/static/path/closestPath/ProcessedPathNodeList.hpp"
#include "src/engine/element/static/path/closestPath/UnprocessedPathNodeList.hpp"
#include "src/engine/element/static/path/MapDetailsInterface.hpp"
#include "src/engine/map/MapCoordinates.hpp"

const qreal DIAGONAL_LENGTH(sqrt(2.0));



ClosestPathFinder::ClosestPathFinder(const MapDetailsInterface& mapDetails) :
    mapDetails(mapDetails)
{

}



QList<MapCoordinates> ClosestPathFinder::getShortestPathToClosestMatch(
    const MapCoordinates& origin,
    std::function<bool(const MapCoordinates&)> match
) const {

    QList<MapCoordinates> path;
    ProcessedPathNodeList closedPathNodes;
    UnprocessedPathNodeList openedPathNodes;
    QHash<PathNode*, PathNode*> parents;

    // Initialize.
    if (origin.isRounded()) {
        openedPathNodes.insertNodeToProcess(new PathNode(origin));
    }
    else {
        // We get here the both nodes around the origin coordinates and initialize them with cost according to origin.
        for (auto originRoundedCoordinates : origin.getClosestRounded()) {
            openedPathNodes.insertNodeToProcess(new PathNode(
                originRoundedCoordinates,
                originRoundedCoordinates.getManhattanDistanceTo(origin)
            ));
        }
    }

    while (openedPathNodes.hasNodeToProcess()) {
        auto current(openedPathNodes.takeClosestToDestination());
        closedPathNodes.markNodeAsProcessed(current);

        qreal neighboursCostFromOrigin(current->getCostFromOrigin() + 1.0);
        for (auto neighbourLocation : current->getNeighbours()) {
            if (match(neighbourLocation)) {
                if (mapDetails.isLocationTraversable(neighbourLocation)) {
                    // If the target is traversable, we add it to the path. Otherwise, we end the path to the location
                    // adjacent to the target.
                    path.prepend(neighbourLocation);
                }
                do {
                    path.prepend(current->getLocation());
                    current = parents.value(current);
                } while (current);

                return path;
            }

            if (closedPathNodes.isNodeForLocationAlreadyProcessed(neighbourLocation)) {
                continue;
            }
            if (!mapDetails.isLocationTraversable(neighbourLocation)) {
                continue;
            }

            if (!openedPathNodes.hasNodeAtLocation(neighbourLocation)) {
                auto neighbour(new PathNode(neighbourLocation, neighboursCostFromOrigin));
                parents[neighbour] = current;
                openedPathNodes.insertNodeToProcess(neighbour);
            }
        }

        neighboursCostFromOrigin = current->getCostFromOrigin() + DIAGONAL_LENGTH;
        for (auto neighbourLocation : current->getDiagonalNeighbours()) {
            if (match(neighbourLocation)) {
                if (mapDetails.isLocationTraversable(neighbourLocation)) {
                    // If the target is traversable, we add it to the path. Otherwise, we end the path to the location
                    // adjacent to the target.
                    path.prepend(neighbourLocation);
                }
                do {
                    path.prepend(current->getLocation());
                    current = parents.value(current);
                } while (current);

                return path;
            }

            if (closedPathNodes.isNodeForLocationAlreadyProcessed(neighbourLocation)) {
                continue;
            }
            if (!mapDetails.isLocationTraversable(neighbourLocation)) {
                continue;
            }

            if (!openedPathNodes.hasNodeAtLocation(neighbourLocation)) {
                auto neighbour(new PathNode(neighbourLocation, neighboursCostFromOrigin));
                parents[neighbour] = current;
                openedPathNodes.insertNodeToProcess(neighbour);
            }
        }
    }

    return path;
}
