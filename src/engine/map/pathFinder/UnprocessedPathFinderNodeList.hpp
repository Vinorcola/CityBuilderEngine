#ifndef UNPROCESSEDPATHFINDERNODELIST_HPP
#define UNPROCESSEDPATHFINDERNODELIST_HPP

#include <QtCore/QLinkedList>

class MapCoordinates;
class PathFinderNode;

/**
 * @brief An list for keeping nodes to be processed by the A* algorithm.
 */
class UnprocessedPathFinderNodeList
{
    private:
        QLinkedList<const PathFinderNode*> list;

    public:
        UnprocessedPathFinderNodeList();

        bool hasNodeToProcess() const;

        void insertNodeToProcess(const PathFinderNode& node);

        const PathFinderNode* findClosestToTargetAtLocation(const MapCoordinates& location) const;

        const PathFinderNode& takeClosestToTarget();
};

#endif // UNPROCESSEDPATHFINDERNODELIST_HPP
