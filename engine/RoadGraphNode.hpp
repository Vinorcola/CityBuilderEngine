#ifndef ROADGRAPHNODE_HPP
#define ROADGRAPHNODE_HPP

#include "engine/Map.hpp"





class RoadGraphNode : public QObject
{
        Q_OBJECT
        
    private:
        Map* map;
        MapCoordinates coordinates;
        RoadGraphNode* northNode;
        RoadGraphNode* southNode;
        RoadGraphNode* eastNode;
        RoadGraphNode* westNode;
        
        
        
    public:
        RoadGraphNode(Map* map, const MapCoordinates& coordinates);
        ~RoadGraphNode();
        
        
        
        const MapCoordinates& getCoordinates() const;
};

#endif // ROADGRAPHNODE_HPP
