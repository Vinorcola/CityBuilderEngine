#include "RoadPathFinderNode.hpp"

#include "engine/map/roadGraph/RoadGraphNode.hpp"



RoadPathFinderNode::RoadPathFinderNode(const RoadGraphNode& roadNode, const qreal costFromOrigin, const MapCoordinates& target) :
    roadNode(roadNode),
    target(target),
    costFromOrigin(costFromOrigin),
    manhattanDistanceToTarget(roadNode.getCoordinates().getManhattanDistanceTo(target)),
    straightDistanceToTarget(roadNode.getCoordinates().getStraightDistanceTo(target))
{

}

bool RoadPathFinderNode::operator ==(const RoadPathFinderNode& other)
{
    return &roadNode == &other.roadNode;
}



bool RoadPathFinderNode::operator ==(const RoadGraphNode& roadNode)
{
    return &this->roadNode == &roadNode;
}



const RoadGraphNode& RoadPathFinderNode::getRoadNode()
{
    return roadNode;
}



bool RoadPathFinderNode::matchTarget() const
{
    return roadNode.getCoordinates() == target;
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



QList<QSharedPointer<RoadPathFinderNode>> RoadPathFinderNode::getNeighbours() const
{
    QList<QSharedPointer<RoadPathFinderNode>> list;

    for (auto neighbour : roadNode.getNeighbourNodeList()) {
        list.append(QSharedPointer<RoadPathFinderNode>(
            new RoadPathFinderNode(*neighbour, costFromOrigin + 1.0, target)
        ));
    }

    return list;
}

