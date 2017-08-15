#include "RoadGraphNode.hpp"

#include "engine/map/roadGraph/RoadGraph.hpp"



RoadGraphNode::RoadGraphNode(RoadGraph* graph, const MapCoordinates& coordinates) :
    QObject(graph),
    coordinates(coordinates),
    northNode(graph->fetchNodeAt(coordinates.getNorth())),
    southNode(graph->fetchNodeAt(coordinates.getSouth())),
    eastNode(graph->fetchNodeAt(coordinates.getEast())),
    westNode(graph->fetchNodeAt(coordinates.getWest()))
{
    if (northNode) {
        northNode->southNode = this;
    }
    if (southNode) {
        southNode->northNode = this;
    }
    if (eastNode) {
        eastNode->westNode = this;
    }
    if (westNode) {
        westNode->eastNode = this;
    }
}



RoadGraphNode::~RoadGraphNode()
{
    // Remove link to this node.
    if (northNode) {
        northNode->southNode = nullptr;
    }
    if (southNode) {
        southNode->northNode = nullptr;
    }
    if (eastNode) {
        eastNode->westNode = nullptr;
    }
    if (westNode) {
        westNode->eastNode = nullptr;
    }
}



const MapCoordinates& RoadGraphNode::getCoordinates() const
{
    return coordinates;
}



QList<const RoadGraphNode*> RoadGraphNode::getNeighbourNodeList() const
{
    QList<const RoadGraphNode*> list;
    if (northNode) {
        list.append(northNode);
    }
    if (southNode) {
        list.append(southNode);
    }
    if (eastNode) {
        list.append(eastNode);
    }
    if (westNode) {
        list.append(westNode);
    }

    return list;
}
