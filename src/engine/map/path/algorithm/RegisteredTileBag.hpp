#ifndef REGISTEREDTILEBAG_HPP
#define REGISTEREDTILEBAG_HPP

#include <list>
#include <QtCore/QHash>

#include "src/defines.hpp"

class Tile;

/**
 * @brief An bag for storing the tiles registered during the execution of an A* algorithm.
 */
class RegisteredTileBag
{
    public:
        RegisteredTileBag(const Tile& origin);

        bool hasTileToProcess() const;
        void registerTile(const Tile& tile, const Tile& predecessor, qreal costFromPredecessor);
        const Tile& takeClosestToDestination();

        QList<const Tile*> constructFinalPath(const Tile& finalTile, bool includeFinalTile);

    private:
        std::list<const Tile*> byBestCostTiles; ///< A list of tiles ordered by they theoretical best cost to destination.
        QHash<const Tile*, const Tile*> predecessors; ///< A hash associating registered tiles with their predecessor.
};

#endif // REGISTEREDTILEBAG_HPP
