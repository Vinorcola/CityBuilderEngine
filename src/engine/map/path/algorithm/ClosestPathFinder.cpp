#include "ClosestPathFinder.hpp"

#include <cmath>
#include <QtCore/QHash>
#include <QtCore/QSet>

#include "src/engine/map/path/algorithm/PathConstructor.hpp"
#include "src/engine/map/path/algorithm/UnprocessedTileList.hpp"
#include "src/engine/map/Tile.hpp"

const qreal DIAGONAL_LENGTH(sqrt(2.0));



QList<const Tile*> ClosestPathFinder::getShortestPathToClosestMatch(const Tile& origin, TileMatcher match)
{
    UnprocessedTileList openedPathTiles;
    QSet<const Tile*> closedTiles;
    PathConstructor parents;

    origin.pathFindingData().reset();
    openedPathTiles.insertTileToProcess(origin);

    while (openedPathTiles.hasTileToProcess()) {
        auto& current(openedPathTiles.takeClosestToDestination());
        closedTiles.insert(&current);

        if (match(current)) {
            return parents.constructPath(current, current.isTraversable());
        }

        qreal neighboursCostFromOrigin(current.pathFindingData().costFromOrigin + 1.0);
        for (auto neighbour : current.relatives().straightNeighbours) {
            if (!closedTiles.contains(neighbour) &&
                neighbour->isTraversable()
            ) {
                if (parents.contains(*neighbour)) {
                    if (neighboursCostFromOrigin < neighbour->pathFindingData().costFromOrigin) {
                        neighbour->pathFindingData().costFromOrigin = neighboursCostFromOrigin;
                        openedPathTiles.reorderTileToProcess(*neighbour);
                        parents.registerTile(*neighbour, current);
                    }
                }
                else {
                    neighbour->pathFindingData().reset(neighboursCostFromOrigin);
                    openedPathTiles.insertTileToProcess(*neighbour);
                    parents.registerTile(*neighbour, current);
                }
            }
        }

        neighboursCostFromOrigin = current.pathFindingData().costFromOrigin + DIAGONAL_LENGTH;
        for (auto neighbour : current.relatives().diagonalNeighbours) {
            if (!closedTiles.contains(neighbour) &&
                neighbour->isTraversable()
            ) {
                if (parents.contains(*neighbour)) {
                    if (neighboursCostFromOrigin < neighbour->pathFindingData().costFromOrigin) {
                        neighbour->pathFindingData().costFromOrigin = neighboursCostFromOrigin;
                        openedPathTiles.reorderTileToProcess(*neighbour);
                        parents.registerTile(*neighbour, current);
                    }
                }
                else {
                    neighbour->pathFindingData().reset(neighboursCostFromOrigin);
                    openedPathTiles.insertTileToProcess(*neighbour);
                    parents.registerTile(*neighbour, current);
                }
            }
        }
    }

    return {};
}
