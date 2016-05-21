#ifndef ABSTRACTBUILDING_HPP
#define ABSTRACTBUILDING_HPP

#include "engine/element/AbstractStaticMapElement.hpp"





class AbstractBuilding : public AbstractStaticMapElement
{
    public:
        AbstractBuilding(const MapArea& area);
};

#endif // ABSTRACTBUILDING_HPP
