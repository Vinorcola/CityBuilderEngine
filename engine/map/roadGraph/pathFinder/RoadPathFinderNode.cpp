#include "RoadPathFinderNode.hpp"

#include "engine/map/roadGraph/RoadGraphNode.hpp"



RoadPathFinderNode::RoadPathFinderNode(QObject* parent, const RoadGraphNode* node, const qreal costFromOrigin, const MapCoordinates& target) :
    QObject(parent),
    node(node),
    target(target),
    costFromOrigin(costFromOrigin),
    manhattanDistanceToTarget(node->getCoordinates().getManhattanDistanceTo(target)),
    straightDistanceToTarget(node->getCoordinates().getStraightDistanceTo(target))
{

}



const RoadGraphNode* RoadPathFinderNode::getNode() const
{
    return node;
}



bool RoadPathFinderNode::matchTarget() const
{
    return node->getCoordinates() == target;
}



qreal RoadPathFinderNode::getCostFromOrigin() const
{
    return costFromOrigin;
}



void RoadPathFinderNode::updateCostFromOrigin(const int cost)
{
    costFromOrigin = cost;
}



qreal RoadPathFinderNode::getEfficiency() const
{
    return costFromOrigin + manhattanDistanceToTarget;
}



qreal RoadPathFinderNode::getStraightDistanceToTarget() const
{
    return straightDistanceToTarget;
}



QList<RoadPathFinderNode*> RoadPathFinderNode::getNeighbours() const
{
    QList<RoadPathFinderNode*> list;

    for (auto neighbour : node->getNeighbourNodeList()) {
        list.append(new RoadPathFinderNode(parent(), neighbour, costFromOrigin + 1.0, target));
    }

    return list;
}

