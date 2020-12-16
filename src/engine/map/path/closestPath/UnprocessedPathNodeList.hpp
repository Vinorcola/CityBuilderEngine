#ifndef UNPROCESSEDPATHNODELIST_HPP
#define UNPROCESSEDPATHNODELIST_HPP

#include <list>

#include "src/defines.hpp"

class TileCoordinates;
class PathNode;

/**
 * @brief An list for keeping nodes to be processed by the path algorithm.
 */
class UnprocessedPathNodeList
{
    private:
        std::list<owner<PathNode*>> list;

    public:
        UnprocessedPathNodeList();

        ~UnprocessedPathNodeList();

        bool hasNodeToProcess() const;

        void insertNodeToProcess(owner<PathNode*> node);

        bool hasNodeAtLocation(const TileCoordinates& location) const;

        owner<PathNode*> takeClosestToDestination();
};

#endif // UNPROCESSEDPATHNODELIST_HPP
