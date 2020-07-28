#include "BuildingWithBehaviors.hpp"

#include "src/engine/element/static/behavior/AbstractActivityBehavior.hpp"
#include "src/engine/element/static/behavior/AbstractBehavior.hpp"
#include "src/engine/element/static/behavior/AbstractWalkerGenerator.hpp"
#include "src/engine/element/static/behavior/BehaviorFactory.hpp"
#include "src/global/conf/BuildingInformation.hpp"



BuildingWithBehaviors::BuildingWithBehaviors(
    QObject* parent,
    const BehaviorFactory* behaviorFactory,
    const BuildingInformation* conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    ProcessableBuilding(parent, *conf, area, entryPoint),
    behaviors()
{
    for (auto behaviorConf : conf->getBehaviors()) {
        behaviors.append(behaviorFactory->generate(this, behaviorConf));
    }
}



void BuildingWithBehaviors::init(const CycleDate& date)
{
    for (auto behavior : behaviors) {
        behavior->init(date);
        auto activityBehavior(dynamic_cast<AbstractActivityBehavior*>(behavior));
        if (activityBehavior) {
            activityBehavior->setActivitySpeedRatio(1.0, date);
        }
    }
}



void BuildingWithBehaviors::process(const CycleDate& date)
{
    for (auto behavior : behaviors) {
        behavior->process(date);
    }
}



bool BuildingWithBehaviors::processInteraction(const CycleDate& date, Character* actor)
{
    for (auto behavior : behaviors) {
        if (behavior->processInteraction(date, actor)) {
            return true;
        }
    }

    return false;
}



void BuildingWithBehaviors::notifyWalkerDestruction()
{
    for (auto behavior : behaviors) {
        auto walkerBehavior(dynamic_cast<AbstractWalkerGenerator*>(behavior));
        if (walkerBehavior) {
            walkerBehavior->clean();
        }
    }
}



bool BuildingWithBehaviors::acceptItem(const ItemInformation* itemType) const
{
    for (auto behavior : behaviors) {
        auto activityBehavior(dynamic_cast<AbstractActivityBehavior*>(behavior));
        if (activityBehavior && activityBehavior->acceptItem(itemType)) {
            return true;
        }
    }

    return false;
}



const QList<AbstractBehavior*>& BuildingWithBehaviors::getBehaviors() const
{
    return behaviors;
}
