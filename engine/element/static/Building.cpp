#include "Building.hpp"

#include "engine/element/static/behavior/AbstractStaticElementBehavior.hpp"
#include "engine/element/static/behavior/AbstractWalkerGenerator.hpp"
#include "engine/element/static/behavior/BehaviorFactory.hpp"
#include "global/conf/StaticElementInformation.hpp"



Building::Building(
    QObject* parent,
    const BehaviorFactory* behaviorFactory,
    const StaticElementInformation* conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    AbstractProcessableStaticMapElement(parent, conf, area, entryPoint),
    behaviors()
{
    for (auto behaviorConf : conf->getBehaviors()) {
        behaviors.append(behaviorFactory->generate(this, behaviorConf));
    }
}



void Building::init(const CycleDate& date)
{
    for (auto behavior : behaviors) {
        behavior->init(date);
        behavior->setActivitySpeedRatio(1.0, date);
    }
}



void Building::process(const CycleDate& date)
{
    for (auto behavior : behaviors) {
        behavior->process(date);
    }
}



bool Building::processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor)
{
    for (auto behavior : behaviors) {
        if (behavior->processInteraction(date, actor)) {
            return true;
        }
    }

    return false;
}



void Building::notifyWalkerDestruction()
{
    for (auto behavior : behaviors) {
        auto walkerBehavior(dynamic_cast<AbstractWalkerGenerator*>(behavior));
        if (walkerBehavior) {
            walkerBehavior->clean();
        }
    }
}
