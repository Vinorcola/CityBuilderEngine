#include "RoadPathFinderNodeList.hpp"

#include "src/engine/map/roadGraph/pathFinder/RoadPathFinderNode.hpp"



RoadPathFinderNodeList::RoadPathFinderNodeList() :
    nodeList()
{

}



bool RoadPathFinderNodeList::contains(RoadPathFinderNode* node) const
{
    for (auto nodeFromList : nodeList) {
        if (nodeFromList->getNode() == node->getNode()) {
            return true;
        }
    }

    return false;
}



void RoadPathFinderNodeList::append(RoadPathFinderNode* node)
{
    nodeList.append(node);
}
