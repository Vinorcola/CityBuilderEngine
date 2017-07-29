#ifndef RANDOMWALKER_HPP
#define RANDOMWALKER_HPP

#include "engine/element/character/AbstractCharacter.hpp"
#include "engine/map/roadGraph/RoadGraphNode.hpp"





class RandomWalker : public AbstractCharacter
{
    private:
        const RoadGraph& roadGraph;



    public:
        RandomWalker(const RoadGraph& roadGraph, const MapCoordinates& initialLocation);



    protected:
        virtual MapCoordinates getNextTargetLocation();
};

#endif // RANDOMWALKER_HPP
