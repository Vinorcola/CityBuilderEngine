#ifndef CLOSESTPATHFINDER_HPP
#define CLOSESTPATHFINDER_HPP

#include <functional>
#include <QtCore/QList>

class Tile;

using TileMatcher = std::function<bool(const Tile&)>;

class ClosestPathFinder
{
    public:
        static QList<const Tile*> getShortestPathToClosestMatch(const Tile& origin, TileMatcher match);
};

#endif // CLOSESTPATHFINDER_HPP
