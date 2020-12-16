#include "UnprocessedPathNodeList.hpp"

#include "src/engine/map/path/closestPath/PathNode.hpp"



UnprocessedPathNodeList::UnprocessedPathNodeList()
{

}



UnprocessedPathNodeList::~UnprocessedPathNodeList()
{
    for (auto element : list) {
        delete element;
    }
}



bool UnprocessedPathNodeList::hasNodeToProcess() const
{
    return !list.empty();
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

    list.push_back(node);
}



bool UnprocessedPathNodeList::hasNodeAtLocation(const TileCoordinates& location) const
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
    auto first(list.front());
    list.pop_front();

    return first;
}
