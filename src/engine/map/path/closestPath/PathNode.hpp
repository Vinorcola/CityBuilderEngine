#ifndef PATHNODE_HPP
#define PATHNODE_HPP

#include "src/global/geometry/TileCoordinates.hpp"

class PathNode
{
    private:
        const TileCoordinates location;
        const qreal costFromOrigin;

    public:
        explicit PathNode(const TileCoordinates& location, const qreal costFromOrigin = 0.0);

        const TileCoordinates& getLocation() const;

        qreal getCostFromOrigin() const;

        /**
         * @brief Get the list of neighbours' coordinates to this node.
         */
        QList<TileCoordinates> getNeighbours() const;

        /**
         * @brief Get the list of diagonal neighbours' coordinates to this node.
         */
        QList<TileCoordinates> getDiagonalNeighbours() const;
};

#endif // PATHNODE_HPP
