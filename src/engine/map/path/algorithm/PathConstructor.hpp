#ifndef PATHCONSTRUCTOR_HPP
#define PATHCONSTRUCTOR_HPP

#include <QtCore/QHash>
#include <QtCore/QList>

class Tile;

class PathConstructor
{
        Q_DISABLE_COPY_MOVE(PathConstructor)

    public:
        PathConstructor();

        bool contains(const Tile& tile) const;

        void registerTile(const Tile& currentTile, const Tile& previousTile);
        QList<const Tile*> constructPath(const Tile& finalTile, bool includeFinalTile);

    private:
        QHash<const Tile*, const Tile*> parents;
};

#endif // PATHCONSTRUCTOR_HPP
