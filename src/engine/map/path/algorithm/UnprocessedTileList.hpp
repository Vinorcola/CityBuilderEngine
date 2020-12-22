#ifndef UNPROCESSEDTILELIST_HPP
#define UNPROCESSEDTILELIST_HPP

#include <list>

#include "src/defines.hpp"

class Tile;

/**
 * @brief An list for keeping tiles to be processed by the A* algorithm.
 */
class UnprocessedTileList
{
    private:
        std::list<const Tile*> list;

    public:
        UnprocessedTileList();

        bool hasTileToProcess() const;
        void insertTileToProcess(const Tile& tile);
        void reorderTileToProcess(const Tile& tile);
        const Tile& takeClosestToDestination();
};

#endif // UNPROCESSEDTILELIST_HPP
