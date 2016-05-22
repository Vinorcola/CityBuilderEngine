#ifndef ABSTRACTSTATICMAPELEMENT_HPP
#define ABSTRACTSTATICMAPELEMENT_HPP

#include "engine/map/MapArea.hpp"





class AbstractStaticMapElement
{
    protected:
        MapArea area;



    public:
        AbstractStaticMapElement(const MapArea& area);
        virtual ~AbstractStaticMapElement() {} // Temporary virtual empty destructor in order to get polymorphism work
                                               // with dynamic_cast.



        const MapArea& getArea() const;
};

#endif // ABSTRACTSTATICMAPELEMENT_HPP
