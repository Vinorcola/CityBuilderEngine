#ifndef PROCESSEDPATHNODELIST_HPP
#define PROCESSEDPATHNODELIST_HPP

#include <QtCore/QList>

#include "src/defines.hpp"

class PathNode;
class TileCoordinates;

/**
 * @brief A list of nodes already processed by the path algorithm.
 */
class ProcessedPathNodeList
{
    private:
        QList<owner<const PathNode*>> list;

    public:
        ProcessedPathNodeList();

        ~ProcessedPathNodeList();

        bool isNodeForLocationAlreadyProcessed(const TileCoordinates& location) const;

        void markNodeAsProcessed(owner<const PathNode*> node);
};

#endif // PROCESSEDPATHNODELIST_HPP
