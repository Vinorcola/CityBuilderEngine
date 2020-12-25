#ifndef TARGETEDPATH_HPP
#define TARGETEDPATH_HPP

#include <QtCore/QList>
#include <QtCore/QWeakPointer>

#include "src/engine/map/path/PathInterface.hpp"

class AbstractStaticElement;
class Tile;

class TargetedPath : public PathInterface
{
    public:
        TargetedPath(
            bool restrictedToRoads,
            const QList<const Tile*>& path,
            optional<QWeakPointer<AbstractStaticElement>> target = {},
            optional<const Tile*> targetTile = nullptr
        );

        optional<QWeakPointer<AbstractStaticElement>> target() const;
        const Tile& targetTile() const;

        virtual bool isObsolete() const override;
        virtual bool isCompleted() const override;

        virtual bool isNextTileValid() const override;
        virtual const Tile& getNextTile() override;

    private:
        const bool restrictedToRoads;
        QList<const Tile*> path;
        optional<QWeakPointer<AbstractStaticElement>> _target;
        optional<const Tile*> _targetTile;
        mutable bool obsolete;
};

#endif // TARGETEDPATH_HPP
