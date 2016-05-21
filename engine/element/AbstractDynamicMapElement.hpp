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



        virtual void process();



        virtual MapCoordinates getNextTargetLocation() = 0;
};

#endif // ABSTRACTDYNAMICMAPELEMENT_HPP
