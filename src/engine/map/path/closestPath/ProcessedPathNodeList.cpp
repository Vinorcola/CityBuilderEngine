#include "ProcessedPathNodeList.hpp"

#include "src/engine/map/path/closestPath/PathNode.hpp"



ProcessedPathNodeList::ProcessedPathNodeList()
{

}



ProcessedPathNodeList::~ProcessedPathNodeList()
{
    qDeleteAll(list);
}



bool ProcessedPathNodeList::isNodeForLocationAlreadyProcessed(const MapCoordinates& location) const
{
    for (auto node : list) {
        if (node->getLocation() == location) {
            return true;
        }
    }

    return false;
}



void ProcessedPathNodeList::markNodeAsProcessed(owner<const PathNode*> node)
{
    list.append(node);
}
