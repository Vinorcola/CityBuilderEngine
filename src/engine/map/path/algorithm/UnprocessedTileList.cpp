#include "UnprocessedTileList.hpp"

#include <cassert>

#include "src/engine/map/Tile.hpp"



UnprocessedTileList::UnprocessedTileList() :
    list()
{

}



bool UnprocessedTileList::hasTileToProcess() const
{
    return !list.empty();
}



void UnprocessedTileList::insertTileToProcess(const Tile& tile)
{
    for (auto iterator(list.begin()), end(list.end()); iterator != end; ++iterator) {
        auto tileFromList(*iterator);
        if (tile.bestTheoreticalCost() < tileFromList->bestTheoreticalCost()) {
            list.insert(iterator, &tile);
            return;
        }
    }

    list.push_back(&tile);
}



void UnprocessedTileList::reorderTileToProcess(const Tile& tile)
{
    list.remove(&tile);
    insertTileToProcess(tile);
}



const Tile& UnprocessedTileList::takeClosestToDestination()
{
    assert(!list.empty());

    auto first(list.front());
    list.pop_front();

    return *first;
}
