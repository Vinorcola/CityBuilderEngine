#ifndef ASTARNODE_HPP
#define ASTARNODE_HPP

#include "src/global/geometry/TileCoordinates.hpp"

/**
 * @brief A node for the path finder algorithm.
 *
 * Note that cost from origin and the Manhattan distance may be a real number if the path is calculated once the
 * character has start to move (it does not have rounded coordinates).
 */
class AStarNode
{
    private:
        const TileCoordinates location;
        qreal costFromOrigin;
        const qreal theoreticalBestDistanceToDestination;
        const qreal straightDistanceToDestination;

    public:
        AStarNode(
            const TileCoordinates& location,
            const TileCoordinates& destination,
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
        const TileCoordinates& getLocation() const;

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
        QList<TileCoordinates> getNeighbours() const;

        /**
         * @brief Get the list of diagonal neighbours' coordinates to this node.
         */
        QList<TileCoordinates> getDiagonalNeighbours() const;

        /**
         * @brief Indicate if this node is closer to the destination compared to the other node.
         */
        bool isTheoreticallyCloserToDestinationThan(const AStarNode& other) const;
};

#endif // ASTARNODE_HPP
