#ifndef ABSTRACTSTATICMAPELEMENT_HPP
#define ABSTRACTSTATICMAPELEMENT_HPP

#include "engine/element/AbstractMapElement.hpp"
#include "engine/map/MapArea.hpp"
#include "global/conf/StaticElementInformation.hpp"

/**
 * @brief Represent a static element on the map.
 *
 * A static element is an element that can't move. It covers an area of the map.
 */
class AbstractStaticMapElement: public AbstractMapElement
{
    protected:
        const StaticElementInformation* conf;
        MapArea area;

    public:
        AbstractStaticMapElement(const StaticElementInformation* conf, const MapArea& area);

        const StaticElementInformation* getConf() const;

        const MapArea& getArea() const;
};

#endif // ABSTRACTSTATICMAPELEMENT_HPP
