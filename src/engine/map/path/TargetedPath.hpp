#ifndef TARGETEDPATH_HPP
#define TARGETEDPATH_HPP

#include <QtCore/QList>

#include "src/engine/map/path/PathInterface.hpp"
#include "src/global/geometry/TileCoordinates.hpp"

class MapDetailsInterface;

class TargetedPath : public PathInterface
{
    private:
        const MapDetailsInterface& mapDetails;
        const bool restrictedToRoads;
        QList<TileCoordinates> path;
        mutable bool obsolete;

    public:
        TargetedPath(
            const MapDetailsInterface& mapDetails,
            const bool restrictedToRoads,
            const QList<TileCoordinates>& path
        );

        virtual bool isObsolete() const override;
        virtual bool isCompleted() const override;

        virtual bool isNextTargetCoordinatesValid() const override;
        virtual TileCoordinates getNextValidTargetCoordinates() override;

        const QList<TileCoordinates>& toCoordinatesList() const;
};

#endif // TARGETEDPATH_HPP
