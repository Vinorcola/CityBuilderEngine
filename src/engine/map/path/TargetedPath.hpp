#ifndef TARGETEDPATH_HPP
#define TARGETEDPATH_HPP

#include <QtCore/QList>

#include "src/engine/map/path/PathInterface.hpp"
#include "src/engine/map/MapCoordinates.hpp"

class MapDetailsInterface;
class PathFinder;

class TargetedPath : public PathInterface
{
    private:
        const MapDetailsInterface& mapDetails;
        const PathFinder& pathFinder;
        MapCoordinates currentLocation;
        const MapCoordinates destination;
        const bool restrictedToRoads;
        QList<MapCoordinates> path;

    public:
        TargetedPath(
            const MapDetailsInterface& mapDetails,
            const PathFinder& pathFinder,
            const MapCoordinates& initialLocation,
            const MapCoordinates& destination,
            const bool restrictedToRoads
        );

        virtual MapCoordinates getNextTargetCoordinates() override;

    private:
        void recalculatePath();
};

#endif // TARGETEDPATH_HPP
