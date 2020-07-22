#include "RoadPathFinder.hpp"

#include <QtAlgorithms>
#include <QtCore/QHash>

#include "engine/map/roadGraph/RoadGraph.hpp"
#include "engine/map/roadGraph/pathFinder/RoadPathFinderNode.hpp"
#include "engine/map/roadGraph/pathFinder/RoadPathFinderNodeList.hpp"
#include "engine/map/roadGraph/pathFinder/RoadPathFinderOrderedNodeList.hpp"
#include "engine/map/MapCoordinates.hpp"



RoadPathFinder::RoadPathFinder(const RoadGraph* roadGraph, const MapCoordinates& origin, const MapCoordinates& target) :
    QObject(),
    path()
{
    RoadPathFinderNodeList closedPathNodes;
    RoadPathFinderOrderedNodeList openedPathNodes;
    QHash<RoadPathFinderNode*, RoadPathFinderNode*> parents;

    // Initialize.
    if (origin.isRounded()) {
        openedPathNodes.insert(new RoadPathFinderNode(this, roadGraph->fetchNodeAt(origin), 0.0, target));
    } else {
        // We get here the both nodes around the origin coordinates and initialize them with cost according to origin.
        for (auto originRoundedCoordinates : origin.getClosestRounded()) {
            openedPathNodes.insert(new RoadPathFinderNode(
                this,
                roadGraph->fetchNodeAt(originRoundedCoordinates),
                originRoundedCoordinates.getManhattanDistanceTo(origin),
                target
            ));
        }
    }

    while (!openedPathNodes.isEmpty()) {
        auto current(openedPathNodes.takeFirst());
        closedPathNodes.append(current);

        if (current->matchTarget()) {
            while (current) {
                path.prepend(current->getNode());
                current = parents.value(current);
            }
            break;
        }

        int currentNeighboursCostFromOrigin(current->getCostFromOrigin() + 1);
        for (auto neighbour : current->getNeighbours()) {
            if (closedPathNodes.contains(neighbour)) {
                // We don't need it anymore.
                delete neighbour;
            } else {
                auto existingNeighbour(openedPathNodes.find(neighbour));
                if (!existingNeighbour) {
                    // Insert the neighbour in the opened path nodes.
                    parents[neighbour] = current;
                    openedPathNodes.insert(neighbour);
                } else {
                    if (currentNeighboursCostFromOrigin < existingNeighbour->getCostFromOrigin()) {
                        // Update the existing neighbour cost.
                        parents[existingNeighbour] = current;
                        existingNeighbour->updateCostFromOrigin(currentNeighboursCostFromOrigin);
                    }

                    // We don't need it anymore.
                    delete neighbour;
                }
            }
        }
    }
}



const QList<const RoadGraphNode*>& RoadPathFinder::getShortestPath() const
{
    return path;
}
