#ifndef ROADPATHGENERATORINTERFACE_HPP
#define ROADPATHGENERATORINTERFACE_HPP

#include <QtCore/QList>

#include "src/engine/map/path/PathInterface.hpp"
#include "src/engine/map/MapCoordinates.hpp"

class RoadPathGeneratorInterface
{
    public:
        virtual ~RoadPathGeneratorInterface() {};

        virtual QList<MapCoordinates> getShortestPathForRoad(
            const MapCoordinates& origin,
            const MapCoordinates& target
        ) const = 0;
};

#endif // ROADPATHGENERATORINTERFACE_HPP
