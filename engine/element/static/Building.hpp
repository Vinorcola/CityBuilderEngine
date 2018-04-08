#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <QtCore/QList>

#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"

class AbstractDynamicMapElement;
class AbstractStaticElementBehavior;
class BehaviorFactory;
class CycleDate;
class MapArea;
class MapCoordinates;
class StaticElementInformation;

/**
 * @brief A building on the map.
 *
 * A building is a static element that can be processed by the engine processor. In order to be processed, it will hold
 * some behaviors. Each behavior will be processed and will fullfill a specific purpose. Behaviors are instanciated
 * using the given building configuration.
 */
class Building : public AbstractProcessableStaticMapElement
{
        Q_OBJECT

    protected:
        QList<AbstractStaticElementBehavior*> behaviors;

    public:
        Building(
            QObject* parent,
            const BehaviorFactory* behaviorFactory,
            const StaticElementInformation* conf,
            const MapArea& area,
            const MapCoordinates& entryPoint
        );

        virtual void init(const CycleDate& date) override;

        virtual void process(const CycleDate& date) override;

        virtual bool processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor) override;

        virtual void notifyWalkerDestruction() override;
};

#endif // BUILDING_HPP
