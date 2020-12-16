#ifndef UNPROCESSEDASTARNODELIST_HPP
#define UNPROCESSEDASTARNODELIST_HPP

#include <list>

#include "src/defines.hpp"

class AStarNode;
class TileCoordinates;

/**
 * @brief An list for keeping nodes to be processed by the A* algorithm.
 */
class UnprocessedAStarNodeList
{
    private:
        std::list<owner<AStarNode*>> list;

    public:
        UnprocessedAStarNodeList();

        ~UnprocessedAStarNodeList();

        bool hasNodeToProcess() const;

        void insertNodeToProcess(owner<AStarNode*> node);

        AStarNode* findClosestToDestinationAtLocation(const TileCoordinates& location) const;

        owner<AStarNode*> takeClosestToDestination();
};

#endif // UNPROCESSEDASTARNODELIST_HPP
