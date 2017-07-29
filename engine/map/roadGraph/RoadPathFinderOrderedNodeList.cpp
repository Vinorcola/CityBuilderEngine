#include "RoadPathFinderOrderedNodeList.hpp"



RoadPathFinderOrderedNodeList::RoadPathFinderOrderedNodeList() :
    nodeList()
{

}



RoadPathFinderOrderedNodeList::~RoadPathFinderOrderedNodeList()
{
    qDeleteAll(nodeList);
    nodeList.clear();
}



bool RoadPathFinderOrderedNodeList::isEmpty() const
{
    return nodeList.isEmpty();
}




RoadPathFinderNode* RoadPathFinderOrderedNodeList::find(RoadPathFinderNode* node) const
{
    for (auto nodeFromList : nodeList) {
        if (&nodeFromList->getNode() == &node->getNode()) {
            return nodeFromList;
        }
    }

    return nullptr;
}



Owner<RoadPathFinderNode*> RoadPathFinderOrderedNodeList::takeFirst()
{
    return nodeList.takeFirst();
}



void RoadPathFinderOrderedNodeList::insert(Owner<RoadPathFinderNode*> node)
{
    for (auto iterator(nodeList.begin()); iterator != nodeList.end(); ++iterator) {
        auto nodeFromList(*iterator);
        if (nodeFromList->getEfficiency() > node->getEfficiency() || (
            nodeFromList->getEfficiency() == node->getEfficiency() &&
            nodeFromList->getStraightDistanceToTarget() > node->getStraightDistanceToTarget()
        )) {
            nodeList.insert(iterator, node);
            return;
        }
    }

    nodeList.append(node);
}
