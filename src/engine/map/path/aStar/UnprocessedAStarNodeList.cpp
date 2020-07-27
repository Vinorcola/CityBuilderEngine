#include "UnprocessedAStarNodeList.hpp"

#include "src/engine/map/path/aStar/AStarNode.hpp"



UnprocessedAStarNodeList::UnprocessedAStarNodeList() :
    list()
{

}



UnprocessedAStarNodeList::~UnprocessedAStarNodeList()
{
    qDeleteAll(list);
}



bool UnprocessedAStarNodeList::hasNodeToProcess() const
{
    return !list.isEmpty();
}



void UnprocessedAStarNodeList::insertNodeToProcess(owner<AStarNode*> node)
{
    for (auto iterator(list.begin()); iterator != list.end(); ++iterator) {
        auto nodeFromList(*iterator);
        if (node->isTheoreticallyCloserToDestinationThan(*nodeFromList)) {
            list.insert(iterator, node);
            return;
        }
    }

    list.append(node);
}



AStarNode* UnprocessedAStarNodeList::findClosestToDestinationAtLocation(const MapCoordinates& location) const
{
    for (auto node : list) {
        if (node->getLocation() == location) {
            return node;
        }
    }

    return nullptr;
}



owner<AStarNode*> UnprocessedAStarNodeList::takeClosestToDestination()
{
    return list.takeFirst();
}
