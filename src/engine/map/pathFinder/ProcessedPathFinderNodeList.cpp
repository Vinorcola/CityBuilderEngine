#include "ProcessedPathFinderNodeList.hpp"

#include "src/engine/map/pathFinder/PathFinderNode.hpp"



ProcessedPathFinderNodeList::ProcessedPathFinderNodeList() :
    list()
{

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



void ProcessedPathFinderNodeList::markNodeAsProcessed(const PathFinderNode& node)
{
    list.append(&node);
}
