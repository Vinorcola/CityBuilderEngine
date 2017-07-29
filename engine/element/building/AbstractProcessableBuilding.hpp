#ifndef ABSTRACTPROCESSABLEBUILDING_HPP
#define ABSTRACTPROCESSABLEBUILDING_HPP

#include "engine/element/building/AbstractBuilding.hpp"
#include "engine/processing/AbstractProcessable.hpp"

class AbstractDynamicMapElement;

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

        /**
         * @brief Process an interaction with a dynamic element and the building.
         * @param actor The actor of the interaction.
         */
        virtual void processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor) = 0;
};

#endif // ABSTRACTPROCESSABLEBUILDING_HPP
