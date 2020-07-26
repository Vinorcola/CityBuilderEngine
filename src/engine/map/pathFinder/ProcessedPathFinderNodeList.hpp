#ifndef PROCESSEDPATHFINDERNODELIST_HPP
#define PROCESSEDPATHFINDERNODELIST_HPP

#include <QtCore/QList>

class MapCoordinates;
class PathFinderNode;

/**
 * @brief A list of nodes already processed by the A* algorithm.
 */
class ProcessedPathFinderNodeList
{
    private:
        QList<const PathFinderNode*> list;

    public:
        ProcessedPathFinderNodeList();

        bool isNodeForLocationAlreadyProcessed(const MapCoordinates& location) const;

        void markNodeAsProcessed(const PathFinderNode& node);
};

#endif // PROCESSEDPATHFINDERNODELIST_HPP
