#ifndef RANDOMWALKER_HPP
#define RANDOMWALKER_HPP

#include "engine/element/character/AbstractCharacter.hpp"
#include "engine/map/RoadGraphNode.hpp"





class RandomWalker : public AbstractCharacter
{
    public:
        RandomWalker(const MapCoordinates& initialLocation);



        virtual MapCoordinates getNextTargetLocation();
};

#endif // RANDOMWALKER_HPP
