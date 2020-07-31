#ifndef PATHNODE_HPP
#define PATHNODE_HPP

#include "src/engine/map/MapCoordinates.hpp"

class PathNode
{
    private:
        const MapCoordinates location;
        const qreal costFromOrigin;

    public:
        explicit PathNode(const MapCoordinates& location, const qreal costFromOrigin = 0.0);

        const MapCoordinates& getLocation() const;

        qreal getCostFromOrigin() const;

        /**
         * @brief Get the list of neighbours' coordinates to this node.
         */
        QList<MapCoordinates> getNeighbours() const;
};

#endif // PATHNODE_HPP
