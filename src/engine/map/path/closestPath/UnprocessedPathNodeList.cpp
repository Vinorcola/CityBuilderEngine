#include "UnprocessedPathNodeList.hpp"

#include "src/engine/map/path/closestPath/PathNode.hpp"



UnprocessedPathNodeList::UnprocessedPathNodeList()
{

}



UnprocessedPathNodeList::~UnprocessedPathNodeList()
{
    qDeleteAll(list);
}



bool UnprocessedPathNodeList::hasNodeToProcess() const
{
    return !list.isEmpty();
}



void UnprocessedPathNodeList::insertNodeToProcess(owner<PathNode*> node)
{
    for (auto iterator(list.begin()); iterator != list.end(); ++iterator) {
        auto nodeFromList(*iterator);
        if (node->getCostFromOrigin() < nodeFromList->getCostFromOrigin()) {
            list.insert(iterator, node);
            return;
        }
    }

    list.append(node);
}



bool UnprocessedPathNodeList::hasNodeAtLocation(const MapCoordinates& location) const
{
    for (auto node : list) {
        if (node->getLocation() == location) {
            return true;
        }
    }

    return false;
}



owner<PathNode*> UnprocessedPathNodeList::takeClosestToDestination()
{
    return list.takeFirst();
}
