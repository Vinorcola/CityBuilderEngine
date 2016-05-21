#ifndef ROAD_HPP
#define ROAD_HPP

#include "engine/element/building/AbstractBuilding.hpp"
#include "engine/map/RoadGraphNode.hpp"





class Road : public AbstractBuilding
{
    private:
        RoadGraphNode* graphNode;



    public:
        Road(Map& map, const MapCoordinates& coordinates);
};

#endif // ROAD_HPP
