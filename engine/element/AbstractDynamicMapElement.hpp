#ifndef ABSTRACTDYNAMICMAPELEMENT_HPP
#define ABSTRACTDYNAMICMAPELEMENT_HPP

#include "engine/map/MapCoordinates.hpp"
#include "engine/processing/AbstractProcessable.hpp"





/**
 * @brief Represent a dynamic element on the map.
 *
 * A dynamic element is an element that can move (e.g. change its coordinates through time). Moving element are of size
 * 1. This implies they do not cover an area. They are just represented by some coordinates.
 */
class AbstractDynamicMapElement : public AbstractProcessable
{
    private:
        MapCoordinates previousLocation;///< The coordinates the element is moving from.
        MapCoordinates currentLocation;///< The current coordinates of the element.
        MapCoordinates targetLocation;///< The coordinates the element is moving to.



    public:
        AbstractDynamicMapElement(const MapCoordinates& initialLocation);



        const MapCoordinates& getPreviousLocation() const;



        const MapCoordinates& getCurrentLocation() const;



        void setNextTargetLocation(const MapCoordinates& nextLocation);



        virtual void process(const CycleDate& date);



    protected:
        virtual MapCoordinates getNextTargetLocation() = 0;



    private:
        void moveToTarget();
};

#endif // ABSTRACTDYNAMICMAPELEMENT_HPP
