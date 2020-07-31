#ifndef CLOSESTPATHFINDER_HPP
#define CLOSESTPATHFINDER_HPP

#include <functional>
#include <QtCore/QList>

class MapCoordinates;
class MapDetailsInterface;

class ClosestPathFinder
{
    private:
        const MapDetailsInterface& mapDetails;

    public:
        explicit ClosestPathFinder(const MapDetailsInterface& mapDetails);

        QList<MapCoordinates> getShortestPathToClosestMatch(
            const MapCoordinates& origin,
            std::function<bool(const MapCoordinates&)> match
        ) const;
};

#endif // CLOSESTPATHFINDER_HPP
