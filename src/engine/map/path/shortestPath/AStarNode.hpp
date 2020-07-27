#ifndef ASTARNODE_HPP
#define ASTARNODE_HPP

#include "src/engine/map/MapCoordinates.hpp"

/**
 * @brief A node for the path finder algorithm.
 *
 * Note that cost from origin and the Manhattan distance may be a real number if the path is calculated once the
 * character has start to move (it does not have rounded coordinates).
 */
class AStarNode
{
    private:
        const MapCoordinates location;
        qreal costFromOrigin;
        const qreal theoreticalBestDistanceToDestination;
        const qreal straightDistanceToDestination;
        const bool useDiagonals;

    public:
        AStarNode(
            const MapCoordinates& location,
            const MapCoordinates& destination,
            const qreal cost,
            const bool useDiagonals
        );

        /**
         * @brief Change the node cost only if the given cost is better.
         */
        void updateCostIfBetter(const qreal cost);

        /**
         * @brief Return the location of the node.
         */
        const MapCoordinates& getLocation() const;

        /**
         * @brief Indicate if this node is at the destination's coordinates.
         */
        bool isDestination() const;

        /**
         * @brief Get the current cost of this node from origin.
         */
        qreal getCostFromOrigin() const;

        /**
         * @brief Get the list of neighbours' coordinates to this node.
         */
        QList<MapCoordinates> getNeighbours() const;

        /**
         * @brief Indicate if this node is closer to the destination compared to the other node.
         */
        bool isTheoreticallyCloserToDestinationThan(const AStarNode& other) const;
};

#endif // ASTARNODE_HPP
