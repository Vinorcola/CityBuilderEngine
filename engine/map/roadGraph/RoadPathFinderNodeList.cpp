#include "RoadPathFinderNodeList.hpp"

RoadPathFinderNodeList::RoadPathFinderNodeList() :
    nodeList()
{

}



RoadPathFinderNodeList::~RoadPathFinderNodeList()
{
    qDeleteAll(nodeList);
    nodeList.clear();
}



bool RoadPathFinderNodeList::contains(RoadPathFinderNode* node) const
{
    for (auto nodeFromList : nodeList) {
        if (&nodeFromList->getNode() == &node->getNode()) {
            return true;
        }
    }

    return false;
}



void RoadPathFinderNodeList::append(RoadPathFinderNode* node)
{
    nodeList.append(node);
}
