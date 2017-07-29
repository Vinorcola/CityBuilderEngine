#ifndef ROADPATHFINDERNODE_H
#define ROADPATHFINDERNODE_H

#include "engine/map/roadGraph/RoadGraphNode.hpp"

template<class RoadPathFinderNode> using Owner = RoadPathFinderNode;

/**
 * @brief A road graph node wrapper used for path finder.
 */
class RoadPathFinderNode
{
    private:
        const RoadGraphNode& node;
        const MapCoordinates& target;
        qreal costFromOrigin;
        const qreal manhattanDistanceToTarget;
        const qreal straightDistanceToTarget;

    public:
        /**
         * @brief Create a new node wrapper.
         * @param node The node to wrap.
         * @param cost The cost from the origin.
         * @param targetNode The target node.
         */
        RoadPathFinderNode(const RoadGraphNode& node, const qreal cost, const MapCoordinates& target);

        /**
         * @brief Get the wrapped graph node.
         */
        const RoadGraphNode& getNode() const;

        /**
         * @brief Indicate if this object wrap the target node.
         */
        bool matchTarget() const;

        /**
         * @brief Get the cost from origin to this node.
         */
        qreal getCostFromOrigin() const;

        /**
         * @brief Update the cost from origin to this node.
         * @param cost
         */
        void updateCostFromOrigin(const int cost);

        /**
         * @brief Get the efficiency of the node in the path to target.
         */
        qreal getEfficiency() const;

        /**
         * @brief Get the straight distance between this node and the target.
         */
        qreal getStraightDistanceToTarget() const;

        /**
         * @brief Get a list of wraper around the node neighbours.
         */
        QList<Owner<RoadPathFinderNode*>> getNeighbours() const;
};

#endif // ROADPATHFINDERNODE_H
