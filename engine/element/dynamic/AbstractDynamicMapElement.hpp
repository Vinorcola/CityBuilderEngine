#ifndef ABSTRACTDYNAMICMAPELEMENT_HPP
#define ABSTRACTDYNAMICMAPELEMENT_HPP

#include <QtCore/QPointer>

#include "engine/element/AbstractMapElement.hpp"
#include "engine/map/MapCoordinates.hpp"
#include "engine/processing/AbstractProcessable.hpp"
#include "global/conf/DynamicElementInformation.hpp"

class AbstractProcessableStaticMapElement;

/**
 * @brief Represent a dynamic element on the map.
 *
 * A dynamic element is an element that can move (e.g. change its coordinates through time). Moving elements do not have
 * any size, so they do not cover any area. They are just represented by some coordinates and should be perceived as
 * mathematical points.
 *
 * Dynamic elements are always issued from a static element. This static element is the one taht requested the dynamic
 * element creation. However, the issuer does not strictly own the dynamic element: all elements are owned by the map
 * object. The dynamic element can still interact with its issuer since it keep a pointer to it.
 *
 * This base class contains all the logic for moving a dynamic element during a the time-cycle processing. So the class
 * that inherit AbstractDynamicMapElement does not have to implement the process() method. However, they must provide
 * implementation for the findNextGoingToLocation() method. This method must return the immediate tile coordinates to
 * move towards.
 */
class AbstractDynamicMapElement : public AbstractProcessable, public AbstractMapElement
{
        Q_OBJECT

    private:
        const DynamicElementInformation* conf;
        const MapCoordinates initialLocation;///< The coordinates of the initial position of the element.
        MapCoordinates moveFromLocation;///< The coordinates of the tile the element is moving from.
        MapCoordinates currentLocation;///< The current coordinates of the element.
        MapCoordinates moveToLocation;///< The coordinates of the tile the element is moving to.

    protected:
        QPointer<AbstractProcessableStaticMapElement> issuer;///< The issuer static element.

    public:
        AbstractDynamicMapElement(QObject* parent, const DynamicElementInformation* conf, AbstractProcessableStaticMapElement* issuer);

        const DynamicElementInformation* getConf() const;

        /**
         * @brief The initial location where the dynamic element appered.
         */
        const MapCoordinates& getInitialLocation() const;

        /**
         * @brief The immediate location coordinates the dynamic element is moving from.
         */
        const MapCoordinates& getComingFromLocation() const;

        /**
         * @brief The current location coordinates of the dynamic element.
         */
        const MapCoordinates& getCurrentLocation() const;

        /**
         * @brief The immediate location coordinates the dynamic element is moving to.
         */
        const MapCoordinates& getGoingToLocation() const;

        /**
         * @brief Make the dynamic element move towards the moveToLocation.
         * @param date The current cycle-time date.
         */
        virtual void process(const CycleDate& date);

    protected:
        /**
         * @brief Find the next location to go to.
         * @param date The current cycle-time date.
         * @return The coordinate to move towards.
         */
        virtual MapCoordinates findNextGoingToLocation(const CycleDate& date) = 0;

    private:
        void moveToTarget();
};

#endif // ABSTRACTDYNAMICMAPELEMENT_HPP
