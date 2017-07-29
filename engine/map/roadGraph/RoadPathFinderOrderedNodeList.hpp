#ifndef ROADPATHFINDERORDEREDNODELIST_HPP
#define ROADPATHFINDERORDEREDNODELIST_HPP

#include <QLinkedList>

#include "engine/map/roadGraph/RoadPathFinderNode.hpp"

class RoadPathFinderOrderedNodeList
{
    private:
        QLinkedList<Owner<RoadPathFinderNode*>> nodeList;

    public:
        RoadPathFinderOrderedNodeList();

        ~RoadPathFinderOrderedNodeList();

        bool isEmpty() const;

        RoadPathFinderNode* find(RoadPathFinderNode* node) const;

        Owner<RoadPathFinderNode*> takeFirst();

        void insert(Owner<RoadPathFinderNode*> node);
};

#endif // ROADPATHFINDERORDEREDNODELIST_HPP
