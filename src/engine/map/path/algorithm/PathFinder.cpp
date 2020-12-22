#include "PathFinder.hpp"

#include <cmath>
#include <QtCore/QSet>

#include "src/engine/map/path/algorithm/RegisteredTileBag.hpp"
#include "src/engine/map/Tile.hpp"

const qreal DIAGONAL_LENGTH(sqrt(2.0));



QList<const Tile*> PathFinder::getShortestPath(
    const Tile& origin,
    const Tile& destination,
    const bool restrictedToRoads
) {
    origin.pathFindingData().resetDestinationCost(destination.pathFindingData(), !restrictedToRoads);
    RegisteredTileBag tilesToProcess(origin);
    QSet<const Tile*> processedTiles;

    while (tilesToProcess.hasTileToProcess()) {
        auto& current(tilesToProcess.takeClosestToDestination());
        processedTiles.insert(&current);

        if (current.pathFindingData().isDestination()) {
            return tilesToProcess.constructFinalPath(current, true);
        }

        for (auto neighbour : current.relatives().straightNeighbours) {
            if (!processedTiles.contains(neighbour) &&
                neighbour->isTraversable() &&
                (!restrictedToRoads || neighbour->isRoad())
            ) {
                neighbour->pathFindingData().resetDestinationCost(destination.pathFindingData(), !restrictedToRoads);
                tilesToProcess.registerTile(*neighbour, current, 1.0);
            }
        }

        if (!restrictedToRoads) {
            for (auto neighbour : current.relatives().diagonalNeighbours) {
                if (!processedTiles.contains(neighbour) &&
                    neighbour->isTraversable() &&
                    (!restrictedToRoads || neighbour->isRoad())
                ) {
                    neighbour->pathFindingData().resetDestinationCost(destination.pathFindingData(), !restrictedToRoads);
                    tilesToProcess.registerTile(*neighbour, current, DIAGONAL_LENGTH);
                }
            }
        }
    }

    return {};
}



QList<const Tile*> PathFinder::getShortestRoadablePath(const Tile& origin, const Tile& destination)
{
    origin.pathFindingData().resetDestinationCost(destination.pathFindingData(), false);
    RegisteredTileBag tilesToProcess(origin);
    QSet<const Tile*> processedTiles;

    while (tilesToProcess.hasTileToProcess()) {
        auto& current(tilesToProcess.takeClosestToDestination());
        processedTiles.insert(&current);

        if (current.pathFindingData().isDestination()) {
            return tilesToProcess.constructFinalPath(current, true);
        }

        for (auto neighbour : current.relatives().straightNeighbours) {
            if (!processedTiles.contains(neighbour) &&
                (neighbour->isConstructible() || neighbour->isRoad())
            ) {
                neighbour->pathFindingData().resetDestinationCost(destination.pathFindingData(), false);
                tilesToProcess.registerTile(*neighbour, current, 1.0);
            }
        }
    }

    return {};
}



QList<const Tile*> PathFinder::getShortestPathToClosestMatch(const Tile& origin, TileMatcher match)
{
    RegisteredTileBag tilesToProcess(origin);
    QSet<const Tile*> processedTiles;

    while (tilesToProcess.hasTileToProcess()) {
        auto& current(tilesToProcess.takeClosestToDestination());
        processedTiles.insert(&current);

        if (match(current)) {
            return tilesToProcess.constructFinalPath(current, current.isTraversable());
        }

        for (auto neighbour : current.relatives().straightNeighbours) {
            if (!processedTiles.contains(neighbour) &&
                (neighbour->isTraversable() || match(*neighbour))
            ) {
                tilesToProcess.registerTile(*neighbour, current, 1.0);
            }
        }

        for (auto neighbour : current.relatives().diagonalNeighbours) {
            if (!processedTiles.contains(neighbour) &&
                (neighbour->isTraversable() || match(*neighbour))
            ) {
                tilesToProcess.registerTile(*neighbour, current, DIAGONAL_LENGTH);
            }
        }
    }

    return {};
}
