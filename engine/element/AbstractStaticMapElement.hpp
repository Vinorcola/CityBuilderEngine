#ifndef ABSTRACTSTATICMAPELEMENT_HPP
#define ABSTRACTSTATICMAPELEMENT_HPP

#include "engine/map/MapArea.hpp"





/**
 * @brief Represent a static element on the map.
 *
 * A static element is an element that can't move. It covers an area of the map.
 */
class AbstractStaticMapElement
{
    protected:
        MapArea area;



    public:
        AbstractStaticMapElement(const MapArea& area);
        virtual ~AbstractStaticMapElement();



        const MapArea& getArea() const;
};

#endif // ABSTRACTSTATICMAPELEMENT_HPP
