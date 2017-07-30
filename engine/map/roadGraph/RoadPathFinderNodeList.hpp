#ifndef ROADPATHFINDERNODELIST_HPP
#define ROADPATHFINDERNODELIST_HPP

#include <QList>

#include "engine/map/roadGraph/RoadPathFinderNode.hpp"

class RoadPathFinderNodeList
{
    private:
        QList<RoadPathFinderNode*> nodeList;

    public:
        RoadPathFinderNodeList();

        bool contains(RoadPathFinderNode* node) const;

        void append(RoadPathFinderNode* node);
};

#endif // ROADPATHFINDERNODELIST_HPP
