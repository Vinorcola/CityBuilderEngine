#include "ShortestPathFinder.hpp"

#include <cmath>
#include <QtCore/QSet>

#include "src/engine/map/path/algorithm/PathConstructor.hpp"
#include "src/engine/map/path/algorithm/UnprocessedTileList.hpp"
#include "src/engine/map/Tile.hpp"

const qreal DIAGONAL_LENGTH(sqrt(2.0));



QList<const Tile*> ShortestPathFinder::getShortestPath(
    const Tile& origin,
    const Tile& destination,
    const bool restrictedToRoads
) {
    UnprocessedTileList openedPathTiles;
    QSet<const Tile*> closedTiles;
    PathConstructor parents;

    origin.pathFindingData().resetWithDestination(!restrictedToRoads, destination.pathFindingData());
    openedPathTiles.insertTileToProcess(origin);

    while (openedPathTiles.hasTileToProcess()) {
        auto& current(openedPathTiles.takeClosestToDestination());
        closedTiles.insert(&current);

        if (current.pathFindingData().isDestination()) {
            return parents.constructPath(current, true);
        }

        qreal neighboursCostFromOrigin(current.pathFindingData().costFromOrigin + 1.0);
        for (auto neighbour : current.relatives().straightNeighbours) {
            if (!closedTiles.contains(neighbour) &&
                neighbour->isTraversable() &&
                (!restrictedToRoads || neighbour->isRoad())
            ) {
                if (parents.contains(*neighbour)) {
                    if (neighboursCostFromOrigin < neighbour->pathFindingData().costFromOrigin) {
                        neighbour->pathFindingData().costFromOrigin = neighboursCostFromOrigin;
                        openedPathTiles.reorderTileToProcess(*neighbour);
                        parents.registerTile(*neighbour, current);
                    }
                }
                else {
                    neighbour->pathFindingData().resetWithDestination(!restrictedToRoads, destination.pathFindingData(), neighboursCostFromOrigin);
                    openedPathTiles.insertTileToProcess(*neighbour);
                    parents.registerTile(*neighbour, current);
                }
            }
        }

        if (!restrictedToRoads) {
            neighboursCostFromOrigin = current.pathFindingData().costFromOrigin + DIAGONAL_LENGTH;
            for (auto neighbour : current.relatives().diagonalNeighbours) {
                if (!closedTiles.contains(neighbour) &&
                    neighbour->isTraversable() &&
                    (!restrictedToRoads || neighbour->isRoad())
                ) {
                    if (parents.contains(*neighbour)) {
                        if (neighboursCostFromOrigin < neighbour->pathFindingData().costFromOrigin) {
                            neighbour->pathFindingData().costFromOrigin = neighboursCostFromOrigin;
                            openedPathTiles.reorderTileToProcess(*neighbour);
                            parents.registerTile(*neighbour, current);
                        }
                    }
                    else {
                        neighbour->pathFindingData().resetWithDestination(!restrictedToRoads, destination.pathFindingData(), neighboursCostFromOrigin);
                        openedPathTiles.insertTileToProcess(*neighbour);
                        parents.registerTile(*neighbour, current);
                    }
                }
            }
        }
    }

    return {};
}



QList<const Tile*> ShortestPathFinder::getShortestRoadablePath(const Tile& origin, const Tile& destination)
{
    UnprocessedTileList openedPathTiles;
    QSet<const Tile*> closedTiles;
    PathConstructor parents;

    origin.pathFindingData().resetWithDestination(false, destination.pathFindingData());
    openedPathTiles.insertTileToProcess(origin);

    while (openedPathTiles.hasTileToProcess()) {
        auto& current(openedPathTiles.takeClosestToDestination());
        closedTiles.insert(&current);

        if (current.pathFindingData().isDestination()) {
            return parents.constructPath(current, true);
        }

        qreal neighboursCostFromOrigin(current.pathFindingData().costFromOrigin + 1.0);
        for (auto neighbour : current.relatives().straightNeighbours) {
            if (!closedTiles.contains(neighbour) &&
                (neighbour->isConstructible() || neighbour->isRoad())
            ) {
                if (parents.contains(*neighbour)) {
                    if (neighboursCostFromOrigin < neighbour->pathFindingData().costFromOrigin) {
                        neighbour->pathFindingData().costFromOrigin = neighboursCostFromOrigin;
                        openedPathTiles.reorderTileToProcess(*neighbour);
                        parents.registerTile(*neighbour, current);
                    }
                }
                else {
                    neighbour->pathFindingData().resetWithDestination(false, destination.pathFindingData(), neighboursCostFromOrigin);
                    openedPathTiles.insertTileToProcess(*neighbour);
                    parents.registerTile(*neighbour, current);
                }
            }
        }
    }

    return {};
}
