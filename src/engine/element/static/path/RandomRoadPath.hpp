#ifndef RANDOMROADPATH_HPP
#define RANDOMROADPATH_HPP

#include "src/engine/element/static/path/PathInterface.hpp"
#include "src/engine/map/MapCoordinates.hpp"

class MapDetailsInterface;

class RandomRoadPath : public PathInterface
{
    private:
        const MapDetailsInterface& mapDetails;
        MapCoordinates previousLocation;
        MapCoordinates currentLocation;
        int wanderingCredits;

    public:
        RandomRoadPath(const MapDetailsInterface& mapDetails, const MapCoordinates& initialLocation, const int wanderingCredits);

        virtual bool isObsolete() const override;

        virtual bool isCompleted() const override;

        virtual MapCoordinates getNextTargetCoordinates() override;

    private:
        MapCoordinates getNextRandomCoordinates() const;
};

#endif // RANDOMROADPATH_HPP
