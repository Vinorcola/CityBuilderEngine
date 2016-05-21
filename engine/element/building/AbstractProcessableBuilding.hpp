#ifndef ABSTRACTPROCESSABLEBUILDING_HPP
#define ABSTRACTPROCESSABLEBUILDING_HPP

#include "engine/element/building/AbstractBuilding.hpp"
#include "engine/processing/AbstractProcessable.hpp"





class AbstractProcessableBuilding : public AbstractBuilding, public AbstractProcessable
{
    public:
        AbstractProcessableBuilding(const MapArea& area);
};

#endif // ABSTRACTPROCESSABLEBUILDING_HPP
