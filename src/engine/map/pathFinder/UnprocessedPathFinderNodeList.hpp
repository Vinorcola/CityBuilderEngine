#ifndef UNPROCESSEDPATHFINDERNODELIST_HPP
#define UNPROCESSEDPATHFINDERNODELIST_HPP

#include <QtCore/QLinkedList>

#include "src/defines.hpp"

class MapCoordinates;
class PathFinderNode;

/**
 * @brief An list for keeping nodes to be processed by the A* algorithm.
 */
class UnprocessedPathFinderNodeList
{
    private:
        QLinkedList<owner<PathFinderNode*>> list;

    public:
        UnprocessedPathFinderNodeList();

        ~UnprocessedPathFinderNodeList();

        bool hasNodeToProcess() const;

        void insertNodeToProcess(owner<PathFinderNode*> node);

        PathFinderNode* findClosestToDestinationAtLocation(const MapCoordinates& location) const;

        owner<PathFinderNode*> takeClosestToDestination();
};

#endif // UNPROCESSEDPATHFINDERNODELIST_HPP
