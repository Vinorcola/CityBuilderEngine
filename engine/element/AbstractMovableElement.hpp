#ifndef ABSTRACTMOVABLEELEMENT_HPP
#define ABSTRACTMOVABLEELEMENT_HPP

#include "engine/element/AbstractMapElement.hpp"
#include "engine/processing/AbstractProcessable.hpp"





class AbstractMovableElement : public AbstractMapElement, public AbstractProcessable
{
    private:
        MapCoordinates currentLocation;
        MapCoordinates targetLocation;



    public:
        AbstractMovableElement(Map& map, const MapCoordinates& initialLocation);



        const MapCoordinates& getCurrentLocation() const;



        void setNextTargetLocation(const MapCoordinates& nextLocation);



        virtual void process();



        virtual MapCoordinates getNextTargetLocation() = 0;
};

#endif // ABSTRACTMOVABLEELEMENT_HPP
