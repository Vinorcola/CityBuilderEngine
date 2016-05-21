#include "Road.hpp"

#include <QDebug>





Road::Road(RoadGraphNode* graphNode) :
    AbstractBuilding(MapArea(graphNode->getCoordinates())),
    graphNode(graphNode)
{
    qDebug() << "Created road at" << graphNode->getCoordinates().toString();
}
