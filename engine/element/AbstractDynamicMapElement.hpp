#ifndef ABSTRACTDYNAMICMAPELEMENT_HPP
#define ABSTRACTDYNAMICMAPELEMENT_HPP

#include "engine/map/MapCoordinates.hpp"
#include "engine/processing/AbstractProcessable.hpp"

/**
 * @brief Represent a dynamic element on the map.
 *
 * A dynamic element is an element that can move (e.g. change its coordinates through time). Moving element do not have
 * any size, so they do not cover any area. They are just represented by some coordinates and should be persive as
 * mathematical point.
 */
class AbstractDynamicMapElement : public AbstractProcessable
{
    private:
        const MapCoordinates initialLocation;///< The coordinates of the initial position of the element.
        MapCoordinates moveFromLocation;///< The coordinates of the tile the element is moving from.
        MapCoordinates currentLocation;///< The current coordinates of the element.
        MapCoordinates moveToLocation;///< The coordinates of the tile the element is moving to.

    public:
        AbstractDynamicMapElement(const MapCoordinates& initialLocation);

        const MapCoordinates& getInitialLocation() const;

        const MapCoordinates& getComingFromLocation() const;

        const MapCoordinates& getCurrentLocation() const;

        const MapCoordinates& getGoingToLocation() const;

        virtual void process(const CycleDate& date);

    protected:
        virtual MapCoordinates findNextGoingToLocation() = 0;

    private:
        void moveToTarget();
};

#endif // ABSTRACTDYNAMICMAPELEMENT_HPP
