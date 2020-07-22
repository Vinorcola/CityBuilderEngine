#include "RoadPathFinderOrderedNodeList.hpp"

#include "engine/map/roadGraph/pathFinder/RoadPathFinderNode.hpp"



RoadPathFinderOrderedNodeList::RoadPathFinderOrderedNodeList() :
    nodeList()
{

}



bool RoadPathFinderOrderedNodeList::isEmpty() const
{
    return nodeList.empty();
}




QSharedPointer<RoadPathFinderNode> RoadPathFinderOrderedNodeList::findForRoad(const RoadGraphNode& roadNode) const
{
    for (auto nodeFromList : nodeList) {
        if (*nodeFromList == roadNode) {
            return nodeFromList;
        }
    }

    return nullptr;
}



QSharedPointer<RoadPathFinderNode> RoadPathFinderOrderedNodeList::takeFirst()
{
    auto firstNode(nodeList.front());
    nodeList.pop_front();

    return firstNode;
}



void RoadPathFinderOrderedNodeList::insert(QSharedPointer<RoadPathFinderNode> node)
{
    for (auto iterator(nodeList.begin()); iterator != nodeList.end(); ++iterator) {
        auto nodeFromList(*iterator);
        if (nodeFromList->getEfficiency() > node->getEfficiency() || (
                nodeFromList->getEfficiency() == node->getEfficiency() &&
                nodeFromList->getStraightDistanceToTarget() > node->getStraightDistanceToTarget()
            )
        ) {
            nodeList.insert(iterator, node);
            return;
        }
    }

    nodeList.push_back(node);
}
