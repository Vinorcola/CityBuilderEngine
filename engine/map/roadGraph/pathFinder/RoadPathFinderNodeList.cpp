#include "RoadPathFinderNodeList.hpp"

#include "engine/map/roadGraph/pathFinder/RoadPathFinderNode.hpp"



RoadPathFinderNodeList::RoadPathFinderNodeList() :
    nodeList()
{

}



bool RoadPathFinderNodeList::contains(const RoadPathFinderNode &node) const
{
    for (auto nodeFromList : nodeList) {
        if (*nodeFromList == node) {
            return true;
        }
    }

    return false;
}



void RoadPathFinderNodeList::append(QSharedPointer<RoadPathFinderNode> node)
{
    nodeList.append(node);
}
