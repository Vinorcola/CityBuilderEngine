#ifndef ABSTRACTBUILDING_HPP
#define ABSTRACTBUILDING_HPP

#include "engine/element/AbstractMotionlessElement.hpp"





class AbstractBuilding : public AbstractMotionlessElement
{
    public:
        AbstractBuilding(Map& map, const MapArea& area);
};

#endif // ABSTRACTBUILDING_HPP
