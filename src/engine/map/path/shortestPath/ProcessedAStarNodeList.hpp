#ifndef PROCESSEDASTARNODELIST_HPP
#define PROCESSEDASTARNODELIST_HPP

#include <QtCore/QList>

#include "src/defines.hpp"

class MapCoordinates;
class AStarNode;

/**
 * @brief A list of nodes already processed by the A* algorithm.
 */
class ProcessedAStarNodeList
{
    private:
        QList<owner<const AStarNode*>> list;

    public:
        ProcessedAStarNodeList();

        ~ProcessedAStarNodeList();

        bool isNodeForLocationAlreadyProcessed(const MapCoordinates& location) const;

        void markNodeAsProcessed(owner<const AStarNode*> node);
};

#endif // PROCESSEDASTARNODELIST_HPP
