#include "RoadGraphNode.hpp"





RoadGraphNode::RoadGraphNode(RoadGraph& graph, const MapCoordinates& coordinates) :
    graph(graph),
    coordinates(coordinates),
    northNode(graph.fetchNodeAt(coordinates.getNorth())),
    southNode(graph.fetchNodeAt(coordinates.getSouth())),
    eastNode(graph.fetchNodeAt(coordinates.getEast())),
    westNode(graph.fetchNodeAt(coordinates.getWest()))
{
    if (northNode != nullptr)
    {
        northNode->southNode = this;
    }
    if (southNode != nullptr)
    {
        southNode->northNode = this;
    }
    if (eastNode != nullptr)
    {
        eastNode->westNode = this;
    }
    if (westNode != nullptr)
    {
        westNode->eastNode = this;
    }
}





RoadGraphNode::~RoadGraphNode()
{
    // Remove link to this node.
    
    // North
    RoadGraphNode* node(graph.fetchNodeAt(coordinates.getNorth()));
    if (node != nullptr)
    {
        node->southNode = nullptr;
    }
    
    // South
    node = graph.fetchNodeAt(coordinates.getSouth());
    if (node != nullptr)
    {
        node->northNode = nullptr;
    }
    
    // East
    node = graph.fetchNodeAt(coordinates.getEast());
    if (node != nullptr)
    {
        node->westNode = nullptr;
    }
    
    // West
    node = graph.fetchNodeAt(coordinates.getWest());
    if (node != nullptr)
    {
        node->eastNode = nullptr;
    }
}





const MapCoordinates& RoadGraphNode::getCoordinates() const
{
    return coordinates;
}
