#ifndef ABSTRACTDYNAMICMAPELEMENT_HPP
#define ABSTRACTDYNAMICMAPELEMENT_HPP

#include "engine/map/MapCoordinates.hpp"
#include "engine/processing/AbstractProcessable.hpp"





class AbstractDynamicMapElement : public AbstractProcessable
{
    private:
        MapCoordinates currentLocation;
        MapCoordinates targetLocation;



    public:
        AbstractDynamicMapElement(const MapCoordinates& initialLocation);



        const MapCoordinates& getCurrentLocation() const;



        void setNextTargetLocation(const MapCoordinates& nextLocation);



        virtual void process(const CycleDate& date);



        virtual MapCoordinates getNextTargetLocation() = 0;



    private:
        void moveToTarget();
};

#endif // ABSTRACTDYNAMICMAPELEMENT_HPP
