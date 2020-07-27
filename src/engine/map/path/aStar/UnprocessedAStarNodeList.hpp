#ifndef UNPROCESSEDASTARNODELIST_HPP
#define UNPROCESSEDASTARNODELIST_HPP

#include <QtCore/QLinkedList>

#include "src/defines.hpp"

class MapCoordinates;
class AStarNode;

/**
 * @brief An list for keeping nodes to be processed by the A* algorithm.
 */
class UnprocessedAStarNodeList
{
    private:
        QLinkedList<owner<AStarNode*>> list;

    public:
        UnprocessedAStarNodeList();

        ~UnprocessedAStarNodeList();

        bool hasNodeToProcess() const;

        void insertNodeToProcess(owner<AStarNode*> node);

        AStarNode* findClosestToDestinationAtLocation(const MapCoordinates& location) const;

        owner<AStarNode*> takeClosestToDestination();
};

#endif // UNPROCESSEDASTARNODELIST_HPP
