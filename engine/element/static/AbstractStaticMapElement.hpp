#ifndef ABSTRACTSTATICMAPELEMENT_HPP
#define ABSTRACTSTATICMAPELEMENT_HPP

#include <QtCore/QObject>

#include "engine/element/AbstractMapElement.hpp"
#include "engine/map/MapArea.hpp"

class StaticElementInformation;

/**
 * @brief The base class for a static element on the map.
 *
 * A static element is an element that do not move. It covers an area of the map. This area will be blocked to other static
 * elements (two static elements cannot share a piece of area).
 */
class AbstractStaticMapElement: public QObject, public AbstractMapElement
{
        Q_OBJECT

    protected:
        const StaticElementInformation* conf;
        MapArea area;

    public:
        AbstractStaticMapElement(const StaticElementInformation* conf, const MapArea& area);

        const StaticElementInformation* getConf() const;

        const MapArea& getArea() const;
};

#endif // ABSTRACTSTATICMAPELEMENT_HPP
