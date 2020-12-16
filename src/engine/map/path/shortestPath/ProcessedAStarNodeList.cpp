#include "ProcessedAStarNodeList.hpp"

#include "src/engine/map/path/shortestPath/AStarNode.hpp"



ProcessedAStarNodeList::ProcessedAStarNodeList() :
    list()
{

}



ProcessedAStarNodeList::~ProcessedAStarNodeList()
{
    qDeleteAll(list);
}



bool ProcessedAStarNodeList::isNodeForLocationAlreadyProcessed(const TileCoordinates& location) const
{
    for (auto node : list) {
        if (node->getLocation() == location) {
            return true;
        }
    }

    return false;
}



void ProcessedAStarNodeList::markNodeAsProcessed(owner<const AStarNode*> node)
{
    list.append(node);
}
