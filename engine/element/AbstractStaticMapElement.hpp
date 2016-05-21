#ifndef ABSTRACTSTATICMAPELEMENT_HPP
#define ABSTRACTSTATICMAPELEMENT_HPP

#include "engine/map/MapArea.hpp"





class AbstractStaticMapElement
{
    protected:
        MapArea area;



    public:
        AbstractStaticMapElement(const MapArea& area);



        const MapArea& getArea() const;
};

#endif // ABSTRACTSTATICMAPELEMENT_HPP
