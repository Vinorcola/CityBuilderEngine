#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <QtCore/QObject>

#include "engine/map/MapArea.hpp"

class StaticElementInformation;

/**
 * @brief The base class for a static element on the map.
 *
 * A static element is an element that do not move. It covers an area of the map. This area will be blocked to other static
 * elements (two static elements cannot share a piece of area).
 */
class Building: public QObject
{
        Q_OBJECT

    protected:
        const StaticElementInformation* conf;
        MapArea area;

    public:
        Building(QObject* parent, const StaticElementInformation* conf, const MapArea& area);

        const StaticElementInformation* getConf() const;

        const MapArea& getArea() const;
};

#endif // BUILDING_HPP
