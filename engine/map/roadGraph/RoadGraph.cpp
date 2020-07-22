#include "RoadGraph.hpp"

#include <QtAlgorithms>

#include "engine/map/roadGraph/RoadGraphNode.hpp"
#include "engine/map/roadGraph/pathFinder/RoadPathFinderNode.hpp"
#include "engine/map/roadGraph/pathFinder/RoadPathFinderNodeList.hpp"
#include "engine/map/roadGraph/pathFinder/RoadPathFinderOrderedNodeList.hpp"
#include "engine/map/MapArea.hpp"
#include "exceptions/UnexpectedException.hpp"



RoadGraph::RoadGraph() :
    nodeList()
{

}



RoadGraph::~RoadGraph()
{
    qDeleteAll(nodeList);
}



RoadGraphNode* RoadGraph::fetchNodeAt(const MapCoordinates& coordinates) const
{
    for (auto node : nodeList) {
        if (node->getCoordinates() == coordinates) {
            return node;
        }
    }

    return nullptr;
}



const RoadGraphNode* RoadGraph::fetchNodeArround(const MapArea& area) const
{
    // Fetch a road node arround the building starting at the coordinates at north of left point of the area covered by
    // the building. The algorithm turn arround the area following clockwise.

    auto left(area.getLeft());
    auto right(area.getRight());
    int moveX(1);
    int moveY(0);

    MapCoordinates coordinates(left.getNorth());
    auto node(fetchNodeAt(coordinates));
    while (!node) {
        coordinates.setX(coordinates.getX() + moveX);
        coordinates.setY(coordinates.getY() + moveY);

        if (moveX == 1 && coordinates.getX() > right.getX()) {
            // Overstep top corner.
            moveX = 0;
            moveY = 1;
        } else if (moveY == 1 && coordinates.getY() > right.getY()) {
            // Overstep right corner.
            moveX = -1;
            moveY = 0;
        } else if (moveX == -1 && coordinates.getX() < left.getX()) {
            // Overstep bottom corner.
            moveY = -1;
            moveX = 0;
        } else if (moveY == -1 && coordinates.getY() < left.getY()) {
            // Overstep left corner. No node found.
            return node; // nulptr
        } else {
            node = fetchNodeAt(coordinates);
        }
    }

    return node;
}



QList<const RoadGraphNode*> RoadGraph::getNextNodeList(const MapCoordinates& comingFromLocation, const MapCoordinates& currentLocation) const
{
    auto node(fetchNodeAt(currentLocation));
    if (!node) {
        throw UnexpectedException("Try to get next nodes from a non existing node.");
    }

    auto list(node->getNeighbourNodeList());
    if (list.size() > 1) {
        // If there is more than one node arround, we delete the node at the previous location so the walker do not turn
        // arround in the middle of the road.
        for (auto element : list) {
            if (element->getCoordinates() == comingFromLocation) {
                list.removeOne(element);
                break;
            }
        }
    }

    return list;
}



QList<const RoadGraphNode*> RoadGraph::getShortestPathBetween(const MapCoordinates& origin, const MapCoordinates& destination) const
{
    QList<const RoadGraphNode*> path;
    RoadPathFinderNodeList closedPathNodes;
    RoadPathFinderOrderedNodeList openedPathNodes;
    QHash<RoadPathFinderNode*, QSharedPointer<RoadPathFinderNode>> parents;

    // Initialize.
    if (origin.isRounded()) {
        openedPathNodes.insert(QSharedPointer<RoadPathFinderNode>(
            new RoadPathFinderNode(*this->fetchNodeAt(origin), 0.0, destination)
        ));
    } else {
        // We get here the both nodes around the origin coordinates and initialize them with cost according to origin.
        for (auto originRoundedCoordinates : origin.getClosestRounded()) {
            openedPathNodes.insert(QSharedPointer<RoadPathFinderNode>(new RoadPathFinderNode(
                *this->fetchNodeAt(originRoundedCoordinates),
                originRoundedCoordinates.getManhattanDistanceTo(origin),
                destination
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

    return path;
}



const RoadGraphNode* RoadGraph::createNode(const MapCoordinates& coordinates)
{
    auto node(fetchNodeAt(coordinates));
    if (node) {
        throw UnexpectedException("A node already exists at the coordinates " + coordinates.toString());
    }

    auto newNode(new RoadGraphNode(*this, coordinates));
    nodeList.append(newNode);

    return newNode;
}



void RoadGraph::deleteNode(const MapCoordinates& coordinates)
{
    auto node(fetchNodeAt(coordinates));
    if (node) {
        delete nodeList.takeAt(nodeList.indexOf(node));
    }
}
