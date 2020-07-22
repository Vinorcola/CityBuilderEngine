#ifndef ABSTRACTPROCESSABLESTATICMAPELEMENT_HPP
#define ABSTRACTPROCESSABLESTATICMAPELEMENT_HPP

#include <functional>

#include "engine/element/static/AbstractStaticMapElement.hpp"
#include "engine/map/MapCoordinates.hpp"
#include "engine/processing/AbstractProcessable.hpp"

class Character;
class CycleDate;
class DynamicElementInformation;
class MapArea;
class StaticElementInformation;

/**
 * @brief The base class for a processable static element on the map.
 *
 * A processable static element is a static element that need to be processed by the engine processor. This mean the
 * element can evolve and/or produce something.
 */
class AbstractProcessableStaticMapElement : public AbstractProcessable, public AbstractStaticMapElement
{
        Q_OBJECT

    private:
        MapCoordinates entryPoint;

    public:
        AbstractProcessableStaticMapElement(
            QObject* parent,
            const StaticElementInformation* conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        const MapCoordinates& getEntryPoint() const;

        /**
         * @brief Process an interaction with a dynamic element and the building.
         * @param actor The actor of the interaction.
         * @return Indicate if the actor was processed or not.
         */
        virtual bool processInteraction(const CycleDate& date, Character* actor) = 0;

        /**
         * @brief Notify that a walker originated from the static element was destroyed.
         * @param date
         */
        virtual void notifyWalkerDestruction() {}

    signals:
        void requestDynamicElementCreation(
            const DynamicElementInformation* elementConf,
            std::function<void(Character*)> afterCreation
        );

        void requestDynamicElementDestruction(
            Character* element,
            std::function<void()> afterDestruction
        );
};

#endif // ABSTRACTPROCESSABLESTATICMAPELEMENT_HPP
