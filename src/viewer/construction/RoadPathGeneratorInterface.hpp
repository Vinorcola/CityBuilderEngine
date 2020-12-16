#ifndef ROADPATHGENERATORINTERFACE_HPP
#define ROADPATHGENERATORINTERFACE_HPP

#include <QtCore/QList>

class TileCoordinates;

class RoadPathGeneratorInterface
{
    public:
        virtual ~RoadPathGeneratorInterface() {};

        virtual QList<TileCoordinates> getShortestPathForRoad(
            const TileCoordinates& origin,
            const TileCoordinates& target
        ) const = 0;
};

#endif // ROADPATHGENERATORINTERFACE_HPP
