#ifndef TRAVERSABLELOCATIONCACHE_HPP
#define TRAVERSABLELOCATIONCACHE_HPP

#include <QtCore/QSet>
#include <QtCore/QString>

class MapArea;
class MapCoordinates;

class TraversableLocationCache
{
    private:
        QSet<QString> nonTraversableCoordinates;

    public:
        TraversableLocationCache();

        void registerNonTraversableLocation(const MapCoordinates& location);

        void registerNonTraversableArea(const MapArea& area);

        bool isLocationTraversable(const MapCoordinates& location) const;

    private:
        QString hashCoordinates(const MapCoordinates& coordinates) const;
};

#endif // TRAVERSABLELOCATIONCACHE_HPP
