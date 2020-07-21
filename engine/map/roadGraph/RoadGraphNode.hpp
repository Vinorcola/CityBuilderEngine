#ifndef ROADGRAPHNODE_HPP
#define ROADGRAPHNODE_HPP

#include <QtCore/QList>

#include "engine/map/MapCoordinates.hpp"

class RoadGraph;

/**
 * @brief The RoadGraphNode class represent a node in the road graph.
 */
class RoadGraphNode
{
    private:
        MapCoordinates coordinates;
        RoadGraphNode* northNode;
        RoadGraphNode* southNode;
        RoadGraphNode* eastNode;
        RoadGraphNode* westNode;

    public:
        RoadGraphNode(const RoadGraph& graph, const MapCoordinates& coordinates);

        ~RoadGraphNode();

        const MapCoordinates& getCoordinates() const;

        QList<const RoadGraphNode*> getNeighbourNodeList() const;
};

#endif // ROADGRAPHNODE_HPP
