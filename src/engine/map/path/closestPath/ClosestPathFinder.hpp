#ifndef CLOSESTPATHFINDER_HPP
#define CLOSESTPATHFINDER_HPP

#include <functional>
#include <QtCore/QList>

class MapDetailsInterface;
class TileCoordinates;

class ClosestPathFinder
{
    private:
        const MapDetailsInterface& mapDetails;

    public:
        explicit ClosestPathFinder(const MapDetailsInterface& mapDetails);

        QList<TileCoordinates> getShortestPathToClosestMatch(
            const TileCoordinates& origin,
            std::function<bool(const TileCoordinates&)> match
        ) const;
};

#endif // CLOSESTPATHFINDER_HPP
