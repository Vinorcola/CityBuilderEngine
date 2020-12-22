#ifndef TARGETEDPATH_HPP
#define TARGETEDPATH_HPP

#include <QtCore/QList>

#include "src/engine/map/path/PathInterface.hpp"

class Tile;

class TargetedPath : public PathInterface
{
    private:
        const bool restrictedToRoads;
        QList<const Tile*> path;
        mutable bool obsolete;

    public:
        TargetedPath(bool restrictedToRoads, const QList<const Tile*>& path);

        virtual bool isObsolete() const override;
        virtual bool isCompleted() const override;

        virtual bool isNextTileValid() const override;
        virtual const Tile& getNextTile() override;
};

#endif // TARGETEDPATH_HPP
