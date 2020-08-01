#include "ClosestPathFinder.hpp"

#include <QtCore/QHash>

#include "src/engine/map/path/closestPath/PathNode.hpp"
#include "src/engine/map/path/closestPath/ProcessedPathNodeList.hpp"
#include "src/engine/map/path/closestPath/UnprocessedPathNodeList.hpp"
#include "src/engine/map/path/MapDetailsInterface.hpp"
#include "src/engine/map/MapCoordinates.hpp"



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

        if (match(current->getLocation())) {
            do {
                path.prepend(current->getLocation());
                current = parents.value(current);
            } while (current);

            return path;
        }

        qreal neighboursCostFromOrigin(current->getCostFromOrigin() + 1.0);
        for (auto neighbourLocation : current->getNeighbours()) {
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
