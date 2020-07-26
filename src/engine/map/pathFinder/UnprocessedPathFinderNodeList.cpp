#include "UnprocessedPathFinderNodeList.hpp"

#include "src/engine/map/pathFinder/PathFinderNode.hpp"



UnprocessedPathFinderNodeList::UnprocessedPathFinderNodeList() :
    list()
{

}



bool UnprocessedPathFinderNodeList::hasNodeToProcess() const
{
    return list.isEmpty();
}



void UnprocessedPathFinderNodeList::insertNodeToProcess(const PathFinderNode& node)
{
    for (auto iterator(list.begin()); iterator != list.end(); ++iterator) {
        auto nodeFromList(*iterator);
        if (node.isTheoreticallyCloserToTargetThan(*nodeFromList)) {
            list.insert(iterator, &node);
            return;
        }
    }

    list.append(&node);
}



const PathFinderNode* UnprocessedPathFinderNodeList::findClosestToTargetAtLocation(const MapCoordinates& location) const
{
    for (auto node : list) {
        if (node->getLocation() == location) {
            return node;
        }
    }

    return nullptr;
}



const PathFinderNode& UnprocessedPathFinderNodeList::takeClosestToTarget()
{
    return *list.takeFirst();
}
