#ifndef PATHFINDERNODE_HPP
#define PATHFINDERNODE_HPP

#include "src/engine/map/MapCoordinates.hpp"

/**
 * @brief A node for the path finder algorithm.
 *
 * Note that cost from origin and the Manhattan distance may be a real number if the path is calculated once the
 * character has start to move (it does not have rounded coordinates).
 */
class PathFinderNode
{
    private:
        const MapCoordinates location;
        qreal costFromOrigin;
        const qreal manhattanDistanceToTarget;
        const qreal straightDistanceToTarget;

    public:
        PathFinderNode(const MapCoordinates& location, const qreal cost, const MapCoordinates& target);

        /**
         * @brief Change the node cost only if the given cost is better.
         */
        void updateCostIfBetter(const qreal cost);

        /**
         * @brief Indicate if this node is at the target's coordinates.
         */
        bool isTarget() const;

        /**
         * @brief Get the current cost of this node from origin.
         */
        qreal getCostFromOrigin() const;

        /**
         * @brief Get the theoretical best cost from origin to target using the current node.
         *
         * This uses the current cost from origin and add the estimated remaining cost to target assuming we have the
         * best path between this node and the target (Manhattan distance).
         */
        qreal getTheoreticalBestCostToReachTarget() const;

        /**
         * @brief Get the straight distance between this node and the target.
         */
        qreal getStraightDistanceToTarget() const;
};

#endif // PATHFINDERNODE_HPP
