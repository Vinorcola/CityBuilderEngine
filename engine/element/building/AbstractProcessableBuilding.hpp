#ifndef ABSTRACTPROCESSABLEBUILDING_HPP
#define ABSTRACTPROCESSABLEBUILDING_HPP

#include "engine/element/building/AbstractBuilding.hpp"
#include "engine/processing/AbstractProcessable.hpp"

/**
 * @brief The base class for buildings that need to be processed.
 */
class AbstractProcessableBuilding : public AbstractBuilding, public AbstractProcessable
{
    private:
        MapCoordinates entryPoint;



    public:
        AbstractProcessableBuilding(const MapArea& area, const MapCoordinates& entryPoint);



        const MapCoordinates& getEntryPoint() const;
};

#endif // ABSTRACTPROCESSABLEBUILDING_HPP
