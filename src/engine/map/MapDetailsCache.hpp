#ifndef MAPDETAILSCACHE_HPP
#define MAPDETAILSCACHE_HPP

#include <QtCore/QSet>
#include <QtCore/QString>

class MapArea;
class MapCoordinates;

class MapDetailsCache
{
    private:
        QSet<QString> nonTraversableCoordinates;
        QSet<QString> roadCoordinates;

    public:
        MapDetailsCache();

        void registerNonTraversableLocation(const MapCoordinates& location);

        void registerNonTraversableArea(const MapArea& area);

        bool isLocationTraversable(const MapCoordinates& location) const;

        void registerRoadLocation(const MapCoordinates& location);

        void unregisterRoadLocation(const MapCoordinates& location);

        bool hasRoadAtLocation(const MapCoordinates& location) const;

        MapCoordinates getBestEntryPointForArea(const MapArea& area) const;

    private:
        QString hashCoordinates(const MapCoordinates& coordinates) const;
};

#endif // MAPDETAILSCACHE_HPP
