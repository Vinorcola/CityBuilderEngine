#include "RoadGraphNode.hpp"



RoadGraphNode::RoadGraphNode(RoadGraph& graph, const MapCoordinates& coordinates) :
    graph(graph),
    coordinates(coordinates),
    northNode(graph.fetchNodeAt(coordinates.getNorth())),
    southNode(graph.fetchNodeAt(coordinates.getSouth())),
    eastNode(graph.fetchNodeAt(coordinates.getEast())),
    westNode(graph.fetchNodeAt(coordinates.getWest()))
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

    // North
    RoadGraphNode* node(graph.fetchNodeAt(coordinates.getNorth()));
    if (node) {
        node->southNode = nullptr;
    }

    // South
    node = graph.fetchNodeAt(coordinates.getSouth());
    if (node) {
        node->northNode = nullptr;
    }

    // East
    node = graph.fetchNodeAt(coordinates.getEast());
    if (node) {
        node->westNode = nullptr;
    }

    // West
    node = graph.fetchNodeAt(coordinates.getWest());
    if (node) {
        node->eastNode = nullptr;
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
