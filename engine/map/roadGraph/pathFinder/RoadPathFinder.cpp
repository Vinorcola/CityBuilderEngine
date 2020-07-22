#include "RoadPathFinder.hpp"

#include <QtAlgorithms>
#include <QtCore/QHash>
#include <QtCore/QSharedPointer>

#include "engine/map/roadGraph/RoadGraph.hpp"
#include "engine/map/roadGraph/pathFinder/RoadPathFinderNode.hpp"
#include "engine/map/roadGraph/pathFinder/RoadPathFinderNodeList.hpp"
#include "engine/map/roadGraph/pathFinder/RoadPathFinderOrderedNodeList.hpp"
#include "engine/map/MapCoordinates.hpp"



RoadPathFinder::RoadPathFinder(const RoadGraph &roadGraph, const MapCoordinates& origin, const MapCoordinates& target) :
    path()
{
    RoadPathFinderNodeList closedPathNodes;
    RoadPathFinderOrderedNodeList openedPathNodes;
    QHash<RoadPathFinderNode*, QSharedPointer<RoadPathFinderNode>> parents;

    // Initialize.
    if (origin.isRounded()) {
        openedPathNodes.insert(QSharedPointer<RoadPathFinderNode>(
            new RoadPathFinderNode(*roadGraph.fetchNodeAt(origin), 0.0, target)
        ));
    } else {
        // We get here the both nodes around the origin coordinates and initialize them with cost according to origin.
        for (auto originRoundedCoordinates : origin.getClosestRounded()) {
            openedPathNodes.insert(QSharedPointer<RoadPathFinderNode>(new RoadPathFinderNode(
                *roadGraph.fetchNodeAt(originRoundedCoordinates),
                originRoundedCoordinates.getManhattanDistanceTo(origin),
                target
            )));
        }
    }

    while (!openedPathNodes.isEmpty()) {
        auto current(openedPathNodes.takeFirst());
        closedPathNodes.append(current);

        if (current->matchTarget()) {
            while (current) {
                path.prepend(&current->getRoadNode());
                current = parents.value(current.get());
            }
            break;
        }

        int currentNeighboursCostFromOrigin(current->getCostFromOrigin() + 1);
        for (auto neighbour : current->getNeighbours()) {
            if (!closedPathNodes.contains(*neighbour)) {
                auto existingNeighbour(openedPathNodes.findForRoad(neighbour->getRoadNode()));
                if (!existingNeighbour) {
                    // Insert the neighbour in the opened path nodes.
                    parents[neighbour.get()] = current;
                    openedPathNodes.insert(neighbour);
                } else {
                    if (currentNeighboursCostFromOrigin < existingNeighbour->getCostFromOrigin()) {
                        // Update the existing neighbour cost.
                        parents[existingNeighbour.get()] = current;
                        existingNeighbour->updateCostFromOrigin(currentNeighboursCostFromOrigin);
                    }
                }
            }
        }
    }
}



const QList<const RoadGraphNode*>& RoadPathFinder::getShortestPath() const
{
    return path;
}
