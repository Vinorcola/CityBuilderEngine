#include "RegisteredTileBag.hpp"

#include <cassert>

#include "src/engine/map/Tile.hpp"



RegisteredTileBag::RegisteredTileBag(const Tile& origin) :
    byBestCostTiles({ &origin }),
    predecessors()
{

}



bool RegisteredTileBag::hasTileToProcess() const
{
    return !byBestCostTiles.empty();
}



void RegisteredTileBag::registerTile(const Tile& tile, const Tile& predecessor, qreal costFromPredecessor)
{
    const qreal TOTAL_COST(predecessor.pathFindingData().costFromOrigin + costFromPredecessor);
    if (predecessors.contains(&tile)) {
        if (TOTAL_COST >= tile.pathFindingData().costFromOrigin) {
            // If the tile is already registered and that the new cost is higher than the previous cost, we abort and
            // do nothing.
            return;
        }
        // As the cost will change, we remove the tile from the ordered list to insert it in it's new correct position
        // later.
        byBestCostTiles.remove(&tile);
    }

    // Update tile cost.
    tile.pathFindingData().costFromOrigin = TOTAL_COST;
    const qreal BEST_THEORETICAL_COST(tile.bestTheoreticalCost());

    // Register the predecessor (will overwrite any previous predecessor).
    predecessors.insert(&tile, &predecessor);

    // Register the tile in the ordered list.
    for (auto iterator(byBestCostTiles.begin()), end(byBestCostTiles.end()); iterator != end; ++iterator) {
        auto tileFromList(*iterator);
        if (BEST_THEORETICAL_COST < tileFromList->bestTheoreticalCost()) {
            byBestCostTiles.insert(iterator, &tile);
            return;
        }
    }
    byBestCostTiles.push_back(&tile);
}



const Tile& RegisteredTileBag::takeClosestToDestination()
{
    assert(!byBestCostTiles.empty());

    auto first(byBestCostTiles.front());
    byBestCostTiles.pop_front();

    return *first;
}



QList<const Tile*> RegisteredTileBag::constructFinalPath(const Tile& finalTile)
{
    QList<const Tile*> path;

    const Tile* tile(&finalTile);
    while (tile) {
        path.prepend(tile);
        tile = predecessors.value(tile);
    }

    return path;
}
