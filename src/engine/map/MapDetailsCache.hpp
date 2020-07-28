#ifndef MAPDETAILSCACHE_HPP
#define MAPDETAILSCACHE_HPP

#include <QtCore/QSet>
#include <QtCore/QString>

class BuildingInformation;
class MapArea;
class MapCoordinates;
class NatureElementInformation;

class MapDetailsCache
{
    private:
        QSet<QString> nonTraversableCoordinates;
        QSet<QString> nonConstructibleCoordinates;
        QSet<QString> roadCoordinates;

    public:
        MapDetailsCache();

        void registerBuildingConstruction(const BuildingInformation& conf, const MapArea& area);

        void registerBuildingDestruction(const MapArea& area);

        void registerNatureElement(const NatureElementInformation& conf, const MapArea& area);

        bool isLocationTraversable(const MapCoordinates& location) const;

        bool isLocationConstructible(const MapCoordinates& location) const;

        bool hasRoadAtLocation(const MapCoordinates& location) const;

        MapCoordinates getBestEntryPointForArea(const MapArea& area) const;

    private:
        QString hashCoordinates(const MapCoordinates& coordinates) const;
};

#endif // MAPDETAILSCACHE_HPP
