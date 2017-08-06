#include "CultureBuilding.hpp"



CultureBuilding::CultureBuilding(QObject* parent, const StaticElementInformation* conf, const MapArea& area, const MapCoordinates& entryPoint) :
    ServiceBuilding(parent, conf, area, entryPoint),
    targetedWalkers(entryPoint.isValid() && conf->getTargetedWalkerConf() ?
        new WalkerPool(this, conf->getTargetedWalkerConf(), conf->getTargetedWalkerGenerationInterval()) :
        nullptr
    )
{
    if (targetedWalkers) {
        connect(targetedWalkers, &WalkerPool::requestDynamicElementCreation, this, &CultureBuilding::requestTargetedWalkerCreation);
    }
}



void CultureBuilding::init(const CycleDate& date)
{
    if (targetedWalkers) {
        targetedWalkers->init(date);
    }
    ServiceBuilding::init(date);
}



void CultureBuilding::process(const CycleDate& date)
{
    if (targetedWalkers) {
        targetedWalkers->process(date);
    }
    ServiceBuilding::process(date);
}



void CultureBuilding::processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor)
{
    if (targetedWalkers) {
        auto walker(dynamic_cast<TargetedWalker*>(actor));
        if (walker && targetedWalkers->contains(walker)) {
            emit requestDynamicElementDestruction(walker, [this, date]() {
                targetedWalkers->clean(date);
            });
            return; // The walker has been deleted. We cannot use actor anymore, so no call to parent
                    // processInteraction() function.
        }
    }
    ServiceBuilding::processInteraction(date, actor);
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
