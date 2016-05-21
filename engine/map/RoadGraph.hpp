#ifndef ROADGRAPH_HPP
#define ROADGRAPH_HPP

#include <QList>

#include "engine/map/MapArea.hpp"
#include "exceptions/UnexpectedException.hpp"

class RoadGraphNode;





/**
 * @brief The road graph is a graph representing the state of the roads on the map.
 *
 * Each road create a new node on the graph. Each node is automatically connected to the eventually existing nodes at
 * direct north, south, west or east. This graph is used to find the shortest path between 2 coordinates on the map (as
 * long as those 2 coordinates are linked together across the graph).
 */
class RoadGraph
{
    private:
        QList<RoadGraphNode*> nodeList;



    public:
        RoadGraph();



        /**
         * @brief Fetch the road graph node located at the given coordinates (or nullptr if none was found).
         */
        RoadGraphNode* fetchNodeAt(const MapCoordinates& coordinates) const;



        /**
         * @brief Fetch the first road graph node arroung the area (or nullptr if none was found).
         */
        RoadGraphNode* fetchNodeArround(const MapArea& area);



        /**
         * @brief Create a new node at the given coordinates.
         *
         * @throw UnexpectedException A node already exists at those coordinates.
         */
        RoadGraphNode* createNode(const MapCoordinates& coordinates);



        /**
         * @brief Delete the node at the given coordinates (if the node exists).
         */
        void deleteNode(const MapCoordinates& coordinates);
};

#endif // ROADGRAPH_HPP
