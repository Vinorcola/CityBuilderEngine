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
class Map;
class MotionHandler;

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
class Character : public QObject, public AbstractProcessable
{
        Q_OBJECT

    private:
        const DynamicElementInformation* conf;
        QPointer<AbstractProcessableStaticMapElement> issuer;///< The issuer static element.
        QPointer<AbstractProcessableStaticMapElement> target;///< The target static element.
        MotionHandler* motionHandler;

    public:
        Character(
            QObject* parent,
            const Map* map,
            const DynamicElementInformation* conf,
            AbstractProcessableStaticMapElement* issuer,
            int randomWalkingCredit = 0
        );

        void assignTarget(AbstractProcessableStaticMapElement* target);

        const DynamicElementInformation* getConf() const;

        /**
         * @brief The current location coordinates of the dynamic element.
         */
        const MapCoordinates& getCurrentLocation() const;

        /**
         * @brief Get the element issuer.
         */
        AbstractProcessableStaticMapElement* getIssuer() const;

        /**
         * @brief Make the dynamic element move towards the moveToLocation.
         * @param date The current cycle-time date.
         */
        virtual void process(const CycleDate& date) override;
};

#endif // CHARACTER_HPP
