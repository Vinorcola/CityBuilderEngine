#ifndef TILE_HPP
#define TILE_HPP

#include <QtCore/QString>
#include <QtCore/QPoint>

class BuildingInformation;
class NatureElementInformation;

class Tile
{
    public:
        Tile(int x, int y);

        const QString& getHash() const;

        // Status.
        bool isConstructible() const;
        bool isTraversable() const;
        bool isRoad() const;
        void registerBuildingConstruction(const BuildingInformation& conf);
        void registerNatureElement(const NatureElementInformation& conf);

        static QString hashCoordinates(int x, int y);
        static QString hashCoordinates(QPoint coordinates);

    private:
        struct Status {
            bool isTraversable;
            bool isConstructible;
            bool isRoad;

            Status();
        };
        struct PathFinding {
            int costFromOrigin;
            int theoreticalBestDistanceToDestination;
        };

        QPoint coordinates;
        QString hash;
        Status status;
};

#endif // TILE_HPP
