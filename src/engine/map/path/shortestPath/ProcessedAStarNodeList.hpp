#ifndef PROCESSEDASTARNODELIST_HPP
#define PROCESSEDASTARNODELIST_HPP

#include <QtCore/QList>

#include "src/defines.hpp"

class AStarNode;
class TileCoordinates;

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

        bool isNodeForLocationAlreadyProcessed(const TileCoordinates& location) const;

        void markNodeAsProcessed(owner<const AStarNode*> node);
};

#endif // PROCESSEDASTARNODELIST_HPP
