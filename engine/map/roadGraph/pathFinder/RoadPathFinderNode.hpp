#ifndef ROADPATHFINDERNODE_H
#define ROADPATHFINDERNODE_H

#include <QtCore/QList>
#include <QtCore/QSharedPointer>

class MapCoordinates;
class RoadGraphNode;

/**
 * @brief A road graph node wrapper used for the path finder algorithm.
 *
 * This node references a road node and add several information like some distances to the target. We can have several
 * nodes (instances) that matches to the same road node, but with different information. But when comparing two nodes
 * together, we only consider the referenced road node.
 */
class RoadPathFinderNode
{
    private:
        const RoadGraphNode& roadNode;
        const MapCoordinates& target;
        qreal costFromOrigin;
        const qreal manhattanDistanceToTarget;
        const qreal straightDistanceToTarget;

    public:
        /**
         * @brief Create a new node wrapper.
         * @param node       The node to wrap.
         * @param cost       The cost from the origin.
         * @param targetNode The target node.
         */
        RoadPathFinderNode(const RoadGraphNode& roadNode, const qreal cost, const MapCoordinates& target);

        /**
         * @brief Compare that nodes matches (they points to the same road node).
         */
        bool operator ==(const RoadPathFinderNode& other);

        /**
         * @brief Indicate if the node references the given road node.
         */
        bool operator ==(const RoadGraphNode& roadNode);

        /**
         * @brief Return the road node associated to this node.
         */
        const RoadGraphNode& getRoadNode();

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
        QList<QSharedPointer<RoadPathFinderNode>> getNeighbours() const;
};

#endif // ROADPATHFINDERNODE_H
