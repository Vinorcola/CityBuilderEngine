#ifndef RANDOMROADPATH_HPP
#define RANDOMROADPATH_HPP

#include "src/engine/map/path/PathInterface.hpp"
#include "src/engine/map/MapCoordinates.hpp"

class MapDetailsInterface;

class RandomRoadPath : public PathInterface
{
    private:
        const MapDetailsInterface& mapDetails;
        MapCoordinates previousLocation;
        MapCoordinates currentLocation;

    public:
        RandomRoadPath(const MapDetailsInterface& mapDetails, const MapCoordinates& initialLocation);

        virtual MapCoordinates getNextTargetCoordinates() override;
};

#endif // RANDOMROADPATH_HPP
