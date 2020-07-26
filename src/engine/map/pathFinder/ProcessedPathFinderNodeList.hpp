#ifndef PROCESSEDPATHFINDERNODELIST_HPP
#define PROCESSEDPATHFINDERNODELIST_HPP

#include <QtCore/QList>

#include "src/defines.hpp"

class MapCoordinates;
class PathFinderNode;

/**
 * @brief A list of nodes already processed by the A* algorithm.
 */
class ProcessedPathFinderNodeList
{
    private:
        QList<owner<const PathFinderNode*>> list;

    public:
        ProcessedPathFinderNodeList();

        ~ProcessedPathFinderNodeList();

        bool isNodeForLocationAlreadyProcessed(const MapCoordinates& location) const;

        void markNodeAsProcessed(owner<const PathFinderNode*> node);
};

#endif // PROCESSEDPATHFINDERNODELIST_HPP
