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

class Building : public AbstractProcessableStaticMapElement
{
        Q_OBJECT

    private:
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
