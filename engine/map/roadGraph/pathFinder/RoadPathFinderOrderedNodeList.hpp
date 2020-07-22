#ifndef ROADPATHFINDERORDEREDNODELIST_HPP
#define ROADPATHFINDERORDEREDNODELIST_HPP

#include <list>
#include <QtCore/QSharedPointer>

class RoadGraphNode;
class RoadPathFinderNode;

/**
 * @brief A list of node for the path finder algorithm that keeps its node ordered according to node efficiency and
 * distance.
 */
class RoadPathFinderOrderedNodeList
{
    private:
        std::list<QSharedPointer<RoadPathFinderNode>> nodeList;

    public:
        RoadPathFinderOrderedNodeList();

        bool isEmpty() const;

        QSharedPointer<RoadPathFinderNode> findForRoad(const RoadGraphNode& roadNode) const;

        QSharedPointer<RoadPathFinderNode> takeFirst();

        void insert(QSharedPointer<RoadPathFinderNode> node);
};

#endif // ROADPATHFINDERORDEREDNODELIST_HPP
