#include "CultureBuilding.hpp"



CultureBuilding::CultureBuilding(
    QObject* parent,
    const SearchEngine* searchEngine,
    const StaticElementInformation* conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) : ServiceBuilding(parent, conf, area, entryPoint),
    targetedWalkers(entryPoint.isValid() && conf->getTargetedWalkerConf() ?
        new TargetedWalkerPool(
            this,
            searchEngine,
            conf->getTargetedWalkerConf(),
            conf->getTargetedWalkerGenerationInterval(),
            conf->getTargetCriteria()
        ) :
        nullptr
    )
{
    if (targetedWalkers) {
        connect(targetedWalkers, &WalkerPool::requestDynamicElementCreation, this, &CultureBuilding::requestTargetedWalkerCreation);
    }
}



void CultureBuilding::init(const CycleDate& date)
{
    ServiceBuilding::init(date);
    if (targetedWalkers) {
        targetedWalkers->init(date);
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
    if (targetedWalkers) {
        auto walker(dynamic_cast<TargetedWalker*>(actor));
        if (walker && targetedWalkers->contains(walker)) {
            emit requestDynamicElementDestruction(walker, [this, date]() {
                targetedWalkers->clean(date);
            });

            return true;
        }
    }
    if (actor->getConf() == conf->getRandomWalkerConf()) {
        // The actor is not a known walker but is of the same type that random walkers emitted. We can then accept it.
        emit requestDynamicElementDestruction(actor, [this, date]() {
            // TODO: Now, building can emit random walkers.
        });

        return true;
    }

    return false;
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
