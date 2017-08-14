#ifndef ROADPATHFINDERNODELIST_HPP
#define ROADPATHFINDERNODELIST_HPP

#include <QtCore/QList>

class RoadPathFinderNode;

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
