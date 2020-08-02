#include "UnprocessedAStarNodeList.hpp"

#include "src/engine/map/path/shortestPath/AStarNode.hpp"



UnprocessedAStarNodeList::UnprocessedAStarNodeList() :
    list()
{

}



UnprocessedAStarNodeList::~UnprocessedAStarNodeList()
{
    for (auto element : list) {
        delete element;
    }
}



bool UnprocessedAStarNodeList::hasNodeToProcess() const
{
    return !list.empty();
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

    list.push_back(node);
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
    auto first(list.front());
    list.pop_front();

    return first;
}
