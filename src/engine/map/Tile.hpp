#ifndef TILE_HPP
#define TILE_HPP

#include <QtCore/QHash>
#include <QtCore/QPoint>
#include <QtCore/QString>

#include "src/defines.hpp"

class BuildingInformation;
class NatureElementInformation;

class Tile
{
        Q_DISABLE_COPY_MOVE(Tile)

    public:
        Tile(int x, int y);

        const QString& getHash() const;

        // Status.
        bool isConstructible() const;
        bool isTraversable() const;
        bool isRoad() const;
        void registerBuildingConstruction(const BuildingInformation& conf);
        void registerNatureElement(const NatureElementInformation& conf);

        // Relatives.
        void pickRelatives(const QHash<QString, Tile*>& tiles);

        static QString hashCoordinates(int x, int y);
        static QString hashCoordinates(QPoint coordinates);

    private:
        struct Status {
            bool isTraversable;
            bool isConstructible;
            bool isRoad;

            Status();
        };
        struct Relatives {
            optional<Tile*> north;
            optional<Tile*> south;
            optional<Tile*> east;
            optional<Tile*> west;
            optional<Tile*> top;
            optional<Tile*> bottom;
            optional<Tile*> left;
            optional<Tile*> right;

            Relatives();
        };
        struct PathFinding {
            int costFromOrigin;
            int theoreticalBestDistanceToDestination;
        };

        QPoint coordinates;
        QString hash;
        Status status;
        Relatives relatives;
        PathFinding pathFinding;
};

#endif // TILE_HPP
