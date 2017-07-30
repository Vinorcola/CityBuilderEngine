#ifndef ABSTRACTDYNAMICMAPELEMENT_HPP
#define ABSTRACTDYNAMICMAPELEMENT_HPP

#include <QWeakPointer>

#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"
#include "engine/map/MapCoordinates.hpp"

/**
 * @brief Represent a dynamic element on the map.
 *
 * A dynamic element is an element that can move (e.g. change its coordinates through time). Moving element do not have
 * any size, so they do not cover any area. They are just represented by some coordinates and should be persive as
 * mathematical point.
 */
class AbstractDynamicMapElement : public AbstractProcessable
{
    private:
        const MapCoordinates initialLocation;///< The coordinates of the initial position of the element.
        MapCoordinates moveFromLocation;///< The coordinates of the tile the element is moving from.
        MapCoordinates currentLocation;///< The current coordinates of the element.
        MapCoordinates moveToLocation;///< The coordinates of the tile the element is moving to.
        qreal speed;///< In number of tile per second.

    protected:
        QWeakPointer<AbstractProcessableStaticMapElement> issuer;///< The issuer static element.

    public:
        AbstractDynamicMapElement(QWeakPointer<AbstractProcessableStaticMapElement> issuer, const qreal speed);

        virtual ~AbstractDynamicMapElement();

        const MapCoordinates& getInitialLocation() const;

        const MapCoordinates& getComingFromLocation() const;

        const MapCoordinates& getCurrentLocation() const;

        const MapCoordinates& getGoingToLocation() const;

        virtual void process(const CycleDate& date);

    protected:
        virtual MapCoordinates findNextGoingToLocation(const CycleDate& date) = 0;

    private:
        void moveToTarget();
};

#endif // ABSTRACTDYNAMICMAPELEMENT_HPP
