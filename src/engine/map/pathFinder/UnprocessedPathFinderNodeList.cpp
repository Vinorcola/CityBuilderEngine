#include "UnprocessedPathFinderNodeList.hpp"

#include "src/engine/map/pathFinder/PathFinderNode.hpp"



UnprocessedPathFinderNodeList::UnprocessedPathFinderNodeList() :
    list()
{

}



UnprocessedPathFinderNodeList::~UnprocessedPathFinderNodeList()
{
    qDeleteAll(list);
}



bool UnprocessedPathFinderNodeList::hasNodeToProcess() const
{
    return !list.isEmpty();
}



void UnprocessedPathFinderNodeList::insertNodeToProcess(owner<PathFinderNode*> node)
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



PathFinderNode* UnprocessedPathFinderNodeList::findClosestToDestinationAtLocation(const MapCoordinates& location) const
{
    for (auto node : list) {
        if (node->getLocation() == location) {
            return node;
        }
    }

    return nullptr;
}



owner<PathFinderNode*> UnprocessedPathFinderNodeList::takeClosestToDestination()
{
    return list.takeFirst();
}
