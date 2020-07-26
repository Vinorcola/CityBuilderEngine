#include "ProcessedPathFinderNodeList.hpp"

#include "src/engine/map/pathFinder/PathFinderNode.hpp"



ProcessedPathFinderNodeList::ProcessedPathFinderNodeList() :
    list()
{

}



ProcessedPathFinderNodeList::~ProcessedPathFinderNodeList()
{
    qDeleteAll(list);
}



bool ProcessedPathFinderNodeList::isNodeForLocationAlreadyProcessed(const MapCoordinates& location) const
{
    for (auto node: list) {
        if (node->getLocation() == location) {
            return true;
        }
    }

    return false;
}



void ProcessedPathFinderNodeList::markNodeAsProcessed(owner<const PathFinderNode*> node)
{
    list.append(node);
}
