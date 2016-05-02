#include "RoadGraphNode.hpp"





RoadGraphNode::RoadGraphNode(Map* map, const MapCoordinates& coordinates) :
    QObject(map),
    coordinates(coordinates),
    northNode(map->fetchRoadGraphNodeAt(coordinates.getNorth())),
    southNode(map->fetchRoadGraphNodeAt(coordinates.getSouth())),
    eastNode(map->fetchRoadGraphNodeAt(coordinates.getEast())),
    westNode(map->fetchRoadGraphNodeAt(coordinates.getWest()))
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
    RoadGraphNode* node(map->fetchRoadGraphNodeAt(coordinates.getNorth()));
    if (node != nullptr)
    {
        node->southNode = nullptr;
    }
    
    // South
    node = map->fetchRoadGraphNodeAt(coordinates.getSouth());
    if (node != nullptr)
    {
        node->northNode = nullptr;
    }
    
    // East
    node = map->fetchRoadGraphNodeAt(coordinates.getEast());
    if (node != nullptr)
    {
        node->westNode = nullptr;
    }
    
    // West
    node = map->fetchRoadGraphNodeAt(coordinates.getWest());
    if (node != nullptr)
    {
        node->eastNode = nullptr;
    }
}





const MapCoordinates&RoadGraphNode::getCoordinates() const
{
    return coordinates;
}
