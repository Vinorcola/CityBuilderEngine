#include "TargetedPath.hpp"

#include <cassert>

#include "src/engine/map/Tile.hpp"



TargetedPath::TargetedPath(
    bool restrictedToRoads,
    const QList<const Tile*>& path,
    optional<QWeakPointer<AbstractStaticElement>> target,
    optional<const Tile*> targetTile
) :
    restrictedToRoads(restrictedToRoads),
    path(path),
    _target(target),
    _targetTile(targetTile),
    obsolete(false)
{

}



optional<QWeakPointer<AbstractStaticElement>> TargetedPath::target() const
{
    return _target;
}



const Tile& TargetedPath::targetTile() const
{
    assert(_targetTile != nullptr);

    return *_targetTile;
}



bool TargetedPath::isObsolete() const
{
    return obsolete;
}



bool TargetedPath::isCompleted() const
{
    return path.isEmpty();
}



bool TargetedPath::isNextTileValid() const
{
    if (obsolete || path.isEmpty()) {
        return false;
    }

    auto nextTile(path.first());
    if (!nextTile->isTraversable()) {
        obsolete = true;
        return false;
    }
    if (restrictedToRoads && !nextTile->isRoad()) {
        obsolete = true;
        return false;
    }

    return true;
}



const Tile& TargetedPath::getNextTile()
{
    assert(!path.isEmpty());

    return *path.takeFirst();
}
