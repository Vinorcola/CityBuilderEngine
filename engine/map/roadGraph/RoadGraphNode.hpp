#ifndef ROADGRAPHNODE_HPP
#define ROADGRAPHNODE_HPP

#include <QtCore/QList>
#include <QtCore/QObject>

#include "engine/map/MapCoordinates.hpp"

class RoadGraph;

/**
 * @brief The RoadGraphNode class represent a node in the road graph.
 */
class RoadGraphNode : public QObject
{
        Q_OBJECT

    private:
        MapCoordinates coordinates;
        RoadGraphNode* northNode;
        RoadGraphNode* southNode;
        RoadGraphNode* eastNode;
        RoadGraphNode* westNode;

    public:
        RoadGraphNode(RoadGraph* graph, const MapCoordinates& coordinates);

        ~RoadGraphNode();

        const MapCoordinates& getCoordinates() const;

        QList<const RoadGraphNode*> getNeighbourNodeList() const;
};

#endif // ROADGRAPHNODE_HPP
