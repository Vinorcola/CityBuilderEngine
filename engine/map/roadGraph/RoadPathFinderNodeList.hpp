#ifndef ROADPATHFINDERNODELIST_HPP
#define ROADPATHFINDERNODELIST_HPP

#include <QList>

#include "engine/map/roadGraph/RoadPathFinderNode.hpp"

class RoadPathFinderNodeList
{
    private:
        QList<Owner<RoadPathFinderNode*>> nodeList;

    public:
        RoadPathFinderNodeList();

        ~RoadPathFinderNodeList();

        bool contains(RoadPathFinderNode* node) const;

        void append(Owner<RoadPathFinderNode*> node);
};

#endif // ROADPATHFINDERNODELIST_HPP
