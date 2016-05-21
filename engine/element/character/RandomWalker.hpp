#ifndef RANDOMWALKER_HPP
#define RANDOMWALKER_HPP

#include "engine/element/character/AbstractCharacter.hpp"
#include "engine/map/RoadGraphNode.hpp"





class RandomWalker : public AbstractCharacter
{
    public:
        RandomWalker(Map& map, const MapCoordinates& initialLocation);
};

#endif // RANDOMWALKER_HPP
