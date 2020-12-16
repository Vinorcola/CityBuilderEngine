#ifndef RANDOMROADPATH_HPP
#define RANDOMROADPATH_HPP

#include "src/engine/map/path/PathInterface.hpp"
#include "src/global/geometry/TileCoordinates.hpp"

class MapDetailsInterface;

class RandomRoadPath : public PathInterface
{
    private:
        const MapDetailsInterface& mapDetails;
        TileCoordinates previousLocation;
        TileCoordinates currentLocation;
        int wanderingCredits;

    public:
        RandomRoadPath(
            const MapDetailsInterface& mapDetails,
            const TileCoordinates& initialLocation,
            const int wanderingCredits
        );

        virtual bool isObsolete() const override;
        virtual bool isCompleted() const override;

        virtual bool isNextTargetCoordinatesValid() const override;
        virtual TileCoordinates getNextValidTargetCoordinates() override;

    private:
        TileCoordinates getNextRandomCoordinates() const;
};

#endif // RANDOMROADPATH_HPP
