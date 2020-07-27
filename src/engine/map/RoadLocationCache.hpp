#ifndef ROADLOCATIONCACHE_HPP
#define ROADLOCATIONCACHE_HPP

#include <QtCore/QSet>
#include <QtCore/QString>

class MapArea;
class MapCoordinates;

class RoadLocationCache
{
    private:
        QSet<QString> roadCoordinates;

    public:
        RoadLocationCache();

        void registerRoadLocation(const MapCoordinates& location);

        void unregisterRoadLocation(const MapCoordinates& location);

        bool hasRoadAtLocation(const MapCoordinates& location) const;

        MapCoordinates getBestEntryPointForArea(const MapArea& area) const;

    private:
        QString hashCoordinates(const MapCoordinates& coordinates) const;
};

#endif // ROADLOCATIONCACHE_HPP
