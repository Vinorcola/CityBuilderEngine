#ifndef ABSTRACTCHARACTER_HPP
#define ABSTRACTCHARACTER_HPP

#include "engine/element/AbstractDynamicMapElement.hpp"





class AbstractCharacter : public AbstractDynamicMapElement
{
    public:
        AbstractCharacter(const MapCoordinates& initialLocation);
};

#endif // ABSTRACTCHARACTER_HPP
