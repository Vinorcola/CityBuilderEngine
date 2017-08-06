#ifndef ABSTRACTPROCESSABLESTATICMAPELEMENT_HPP
#define ABSTRACTPROCESSABLESTATICMAPELEMENT_HPP

#include "engine/element/dynamic/AbstractDynamicMapElement.hpp"
#include "engine/element/static/AbstractStaticMapElement.hpp"
#include "engine/processing/AbstractProcessable.hpp"
#include "global/conf/DynamicElementInformation.hpp"

class AbstractDynamicMapElement;

/**
 * @brief The base class for buildings that need to be processed.
 */
class AbstractProcessableStaticMapElement : public AbstractProcessable, public AbstractStaticMapElement
{
        Q_OBJECT

    private:
        MapCoordinates entryPoint;

    public:
        AbstractProcessableStaticMapElement(QObject* parent, const StaticElementInformation* conf, const MapArea& area, const MapCoordinates& entryPoint);

        const MapCoordinates& getEntryPoint() const;

        /**
         * @brief Process an interaction with a dynamic element and the building.
         * @param actor The actor of the interaction.
         */
        virtual void processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor) = 0;

    signals:
        void requestDynamicElementCreation(
            const DynamicElementInformation* elementConf,
            std::function<void(AbstractDynamicMapElement*)> afterCreation
        );

        void requestDynamicElementDestruction(
            AbstractDynamicMapElement* element,
            std::function<void()> afterDestruction
        );
};

#endif // ABSTRACTPROCESSABLESTATICMAPELEMENT_HPP
