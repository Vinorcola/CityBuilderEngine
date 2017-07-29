#include "RoadPathFinderNode.hpp"



RoadPathFinderNode::RoadPathFinderNode(const RoadGraphNode& node, const qreal costFromOrigin, const MapCoordinates& target) :
    node(node),
    target(target),
    costFromOrigin(costFromOrigin),
    manhattanDistanceToTarget(node.getCoordinates().getManhattanDistanceTo(target)),
    straightDistanceToTarget(node.getCoordinates().getStraightDistanceTo(target))
{

}



const RoadGraphNode& RoadPathFinderNode::getNode() const
{
    return node;
}



bool RoadPathFinderNode::matchTarget() const
{
    return node.getCoordinates() == target;
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



QList<Owner<RoadPathFinderNode*>> RoadPathFinderNode::getNeighbours() const
{
    QList<Owner<RoadPathFinderNode*>> list;

    for (auto neighbour : node.getNeighbourNodeList()) {
        list.append(new RoadPathFinderNode(*neighbour, costFromOrigin + 1.0, target));
    }

    return list;
}

