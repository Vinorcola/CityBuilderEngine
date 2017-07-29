#ifndef ROAD_HPP
#define ROAD_HPP

#include "engine/element/building/AbstractBuilding.hpp"
#include "engine/map/roadGraph/RoadGraphNode.hpp"





class Road : public AbstractBuilding
{
    private:
        const RoadGraphNode* graphNode;



    public:
        Road(const RoadGraphNode* graphNode);
};

#endif // ROAD_HPP
