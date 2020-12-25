#ifndef TARGETEDPATH_HPP
#define TARGETEDPATH_HPP

#include <QtCore/QList>
#include <QtCore/QWeakPointer>

#include "src/engine/map/path/PathInterface.hpp"

class AbstractStaticElement;
class Tile;

class TargetedPath : public PathInterface
{
    private:
        const bool restrictedToRoads;
        QList<const Tile*> path;
        QWeakPointer<AbstractStaticElement> _target;
        mutable bool obsolete;

    public:
        TargetedPath(
            bool restrictedToRoads,
            const QList<const Tile*>& path,
            QWeakPointer<AbstractStaticElement> target = {}
        );

        QWeakPointer<AbstractStaticElement> target() const;

        virtual bool isObsolete() const override;
        virtual bool isCompleted() const override;

        virtual bool isNextTileValid() const override;
        virtual const Tile& getNextTile() override;
};

#endif // TARGETEDPATH_HPP
