#ifndef ABSTRACTSTATICMAPELEMENT_HPP
#define ABSTRACTSTATICMAPELEMENT_HPP

#include "engine/element/AbstractMapElement.hpp"
#include "engine/map/MapArea.hpp"

/**
 * @brief Represent a static element on the map.
 *
 * A static element is an element that can't move. It covers an area of the map.
 */
class AbstractStaticMapElement: public AbstractMapElement
{
    public:
        enum class Type
        {
            None = 0,
            House,
            Maintenance,
            Road,
        };
    protected:
        MapArea area;

    public:
        AbstractStaticMapElement(const MapArea& area);

        const MapArea& getArea() const;
};

#endif // ABSTRACTSTATICMAPELEMENT_HPP
