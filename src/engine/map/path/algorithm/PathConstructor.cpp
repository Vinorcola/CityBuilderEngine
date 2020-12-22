#include "PathConstructor.hpp"



PathConstructor::PathConstructor() :
    parents()
{

}



bool PathConstructor::contains(const Tile& tile) const
{
    return parents.contains(&tile);
}



void PathConstructor::registerTile(const Tile& currentTile, const Tile& previousTile)
{
    parents.insert(&currentTile, &previousTile);
}



QList<const Tile*> PathConstructor::constructPath(const Tile& finalTile, bool includeFinalTile)
{
    QList<const Tile*> path;

    if (includeFinalTile) {
        path.prepend(&finalTile);
    }

    const Tile* tile(parents.value(&finalTile));
    while (tile) {
        path.prepend(tile);
        tile = parents.value(tile);
    }

    return path;
}
