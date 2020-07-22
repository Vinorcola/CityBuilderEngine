#ifndef ROADPATHFINDERNODELIST_HPP
#define ROADPATHFINDERNODELIST_HPP

#include <QtCore/QList>
#include <QtCore/QSharedPointer>

class RoadPathFinderNode;

/**
 * @brief A simple list of node for the path finder algorithm.
 */
class RoadPathFinderNodeList
{
    private:
        QList<QSharedPointer<RoadPathFinderNode>> nodeList;

    public:
        RoadPathFinderNodeList();

        bool contains(const RoadPathFinderNode& node) const;

        void append(QSharedPointer<RoadPathFinderNode> node);
};

#endif // ROADPATHFINDERNODELIST_HPP
