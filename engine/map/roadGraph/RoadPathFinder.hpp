#ifndef ROADPATHFINDER_HPP
#define ROADPATHFINDER_HPP

#include <QList>

#include "engine/map/roadGraph/RoadGraphNode.hpp"

/**
 * @brief The RoadPathFinder class run an A* algorithm on a road graph to find the shortest path between two nodes.
 */
class RoadPathFinder : public QObject
{
        Q_OBJECT

    private:
        QList<const RoadGraphNode*> path;

    public:
        /**
         * @brief Find the shortest path between origin and target.
         * @param roadGraph The road grpah to use.
         * @param origin Must be coordinates whoses both closest rounded match a road node.
         * @param target Must be rounded coordinates that match a road node.
         */
        RoadPathFinder(const RoadGraph* roadGraph, const MapCoordinates& origin, const MapCoordinates& target);

        /**
         * @brief Get the shortest path.
         * @return A list of road node from the origin to the target or an empty path is no path available.
         */
        const QList<const RoadGraphNode*>& getShortestPath() const;
};

#endif // ROADPATHFINDER_HPP
