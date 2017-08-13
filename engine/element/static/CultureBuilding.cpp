#include "CultureBuilding.hpp"

#include "engine/element/static/behavior/ConditionalRandomWalkerGenerator.hpp"



CultureBuilding::CultureBuilding(
    QObject* parent,
    const SearchEngine* searchEngine,
    const StaticElementInformation* conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    ServiceBuilding(parent, conf, area, entryPoint),
    targetedWalkers(entryPoint.isValid() && conf->getTargetedWalkerConf() ?
        new TargetedWalkerGenerator(
            this,
            searchEngine,
            conf->getTargetCriteria(),
            conf->getTargetedWalkerConf(),
            conf->getTargetedWalkerGenerationInterval()
        ) :
        nullptr
    )
{
    if (targetedWalkers) {
        connect(targetedWalkers, &TargetedWalkerGenerator::requestDynamicElementCreation, this, &CultureBuilding::requestTargetedWalkerCreation);
        connect(targetedWalkers, &TargetedWalkerGenerator::requestDynamicElementDestruction, this, &ServiceBuilding::requestDynamicElementDestruction);
    }
//    return conf->getNeededWalker() ?
//        new ConditionalRandomWalkerGenerator(
//            this,
//            conf->getRandomWalkerConf(),
//            conf->getNeededWalker(),
//            conf->getRandomWalkerGenerationInterval(),
//            conf->getMaxNumberOfRandomWalkers()
//        ) :
//        ServiceBuilding::generateRandomWalker(conf);
}



void CultureBuilding::init(const CycleDate& date)
{
    ServiceBuilding::init(date);
    if (targetedWalkers) {
        targetedWalkers->init(date);
        if (getEntryPoint().isValid()) {
            targetedWalkers->setGenerationSpeedRatio(1.0, date);
        }
    }
}



void CultureBuilding::process(const CycleDate& date)
{
    ServiceBuilding::process(date);
    if (targetedWalkers) {
        targetedWalkers->process(date);
    }
}



bool CultureBuilding::processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor)
{
    if (ServiceBuilding::processInteraction(date, actor)) {
        return true;
    }
    if (targetedWalkers && targetedWalkers->processInteraction(date, actor)) {
        return true;
    }

    return false;
}



void CultureBuilding::notifyWalkerDestruction()
{
    ServiceBuilding::notifyWalkerDestruction();
    targetedWalkers->clean();
}



void CultureBuilding::requestTargetedWalkerCreation(
    const DynamicElementInformation* elementConf,
    std::function<void (AbstractDynamicMapElement*)> afterCreation
) {
    emit requestDynamicElementCreation(elementConf, [this, &afterCreation](AbstractDynamicMapElement* element) {
        auto walker(dynamic_cast<TargetedWalker*>(element));
        walker->assignTarget(nullptr); // TODO: Fetch a target.
        afterCreation(element);
    });
}
