#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <QtCore/QObject>
#include <QtCore/QPointer>

#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"
#include "engine/element/AbstractMapElement.hpp"
#include "engine/map/MapCoordinates.hpp"
#include "engine/processing/AbstractProcessable.hpp"

class CycleDate;
class DynamicElementInformation;

/**
 * @brief A character on the map.
 *
 * A character is a dynamic element that can move (e.g. change its coordinates through time). It do not have any size,
 * so they do not cover any area. They are just represented by some coordinates and should be perceived as mathematical
 * points.
 *
 * Characters are always issued from a building. This building (named the character's issuer) does not strictly own the
 * character: all characters are owned by the map. Furthermore, a charater can be kept alive even if the issuer has been
 * destroyed.
 */
class Character : public AbstractProcessable
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
        Character(QObject* parent, const DynamicElementInformation* conf, AbstractProcessableStaticMapElement* issuer);

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
         * @brief Get the element issuer.
         */
        AbstractProcessableStaticMapElement* getIssuer() const;

        /**
         * @brief Make the dynamic element move towards the moveToLocation.
         * @param date The current cycle-time date.
         */
        virtual void process(const CycleDate& date) override;

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

#endif // CHARACTER_HPP
