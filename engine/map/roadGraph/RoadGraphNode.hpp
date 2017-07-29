#ifndef ROADGRAPHNODE_HPP
#define ROADGRAPHNODE_HPP

#include "engine/map/MapCoordinates.hpp"
#include "engine/map/roadGraph/RoadGraph.hpp"

/**
 * @brief The RoadGraphNode class represent a node in the road graph.
 */
class RoadGraphNode
{
    private:
        RoadGraph& graph;
        MapCoordinates coordinates;
        RoadGraphNode* northNode;
        RoadGraphNode* southNode;
        RoadGraphNode* eastNode;
        RoadGraphNode* westNode;

    public:
        RoadGraphNode(RoadGraph& graph, const MapCoordinates& coordinates);

        ~RoadGraphNode();

        const MapCoordinates& getCoordinates() const;

        QList<const RoadGraphNode*> getNeighbourNodeList() const;
};

#endif // ROADGRAPHNODE_HPP
