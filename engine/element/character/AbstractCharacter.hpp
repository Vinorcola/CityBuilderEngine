#ifndef ABSTRACTCHARACTER_HPP
#define ABSTRACTCHARACTER_HPP

#include "engine/element/AbstractMovableElement.hpp"





class AbstractCharacter : public AbstractMovableElement
{
    public:
        AbstractCharacter(Map& map, const MapCoordinates& initialLocation);
};

#endif // ABSTRACTCHARACTER_HPP
