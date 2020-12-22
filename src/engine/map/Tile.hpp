#ifndef TILE_HPP
#define TILE_HPP

#include <QtCore/QHash>
#include <QtCore/QPoint>
#include <QtCore/QString>

#include "src/global/geometry/TileCoordinates.hpp"
#include "src/defines.hpp"

class BuildingInformation;
class ClosestPathFinder;
class NatureElementInformation;
class PathFinder;

class Tile
{
        Q_DISABLE_COPY_MOVE(Tile)

    private:
        class PathFinding;
        struct Relatives;

    public:
        Tile(int x, int y);

        const TileCoordinates& coordinates() const;

        // Status.
        bool isConstructible() const;
        bool isTraversable() const;
        bool isRoad() const;
        void registerBuildingConstruction(const BuildingInformation& conf);
        void registerNatureElement(const NatureElementInformation& conf);

        // Relatives.
        const Relatives& relatives() const;
        void pickRelatives(const QHash<QString, Tile*>& tiles);

        // Path finding.
        PathFinding& pathFindingData() const;
        qreal bestTheoreticalCost() const;

    private:
        struct Status {
            bool isTraversable;
            bool isConstructible;
            bool isRoad;

            Status();
        };
        struct Relatives {
            QList<const Tile*> straightNeighbours;
            QList<const Tile*> diagonalNeighbours;
        };
        /**
         * @brief Data needed for the path finding algorithm.
         *
         * This data should not be used or interfered from outside the path finding algorithm. As this data does not
         * impact the representation of the tile, it is made mutable to allow its modification even with a const
         * reference to the tile.
         *
         * In a previous implementation, this data were in a different class, but the path finding algorithm was
         * constantly allocating & deallocating memory. For performance matter, we attach it to the tile object.
         */
        class PathFinding {
            friend PathFinder;
            friend Tile;

            private:
                PathFinding(const TileCoordinates& coordinates);
                void reset(qreal initialCost = 0.0);
                void resetWithDestination(bool allowDiagonals, const PathFinding& destination, qreal initialCost = 0.0);
                bool isDestination() const;

                const TileCoordinates& coordinates;
                qreal costFromOrigin;
                qreal theoreticalBestDistanceToDestination;
                optional<Tile*> parent;
        };

        TileCoordinates _coordinates;
        Status status;
        Relatives _relatives;
        mutable PathFinding pathFinding;
};

#endif // TILE_HPP
