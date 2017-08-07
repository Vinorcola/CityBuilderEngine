#include "ServiceBuilding.hpp"

#include "engine/map/Map.hpp"



ServiceBuilding::ServiceBuilding(QObject* parent, const StaticElementInformation* conf, const MapArea& area, const MapCoordinates& entryPoint) :
    AbstractProcessableStaticMapElement(parent, conf, area, entryPoint),
    randomWalkers(entryPoint.isValid() && conf->getRandomWalkerConf() ?
        new WalkerPool(this, conf->getRandomWalkerConf(), conf->getRandomWalkerGenerationInterval(), conf->getMaxNumberOfRandomWalkers()) :
        nullptr
    ),
    canGenerateWalkersUntil()
{
    if (randomWalkers) {
        connect(randomWalkers, &WalkerPool::requestDynamicElementCreation, this, &ServiceBuilding::requestDynamicElementCreation);
    }
}



void ServiceBuilding::init(const CycleDate& date)
{
    if (randomWalkers && !conf->getNeededWalker()) {
        randomWalkers->init(date);
    }
}



void ServiceBuilding::process(const CycleDate& date)
{
    if (randomWalkers && (!conf->getNeededWalker() || date <= canGenerateWalkersUntil)) {
        randomWalkers->process(date);
    }
}



bool ServiceBuilding::processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor)
{
    if (randomWalkers) {
        auto walker(dynamic_cast<TargetedWalker*>(actor));
        if (walker && randomWalkers->contains(walker)) {
            emit requestDynamicElementDestruction(walker, [this, date]() {
                randomWalkers->clean(date);
            });

            return true;
        }
    }
    if (actor->getConf() == conf->getNeededWalker()) {
        auto issuer(actor->getIssuer());
        emit requestDynamicElementDestruction(actor, [this, date, issuer]() {
            if (issuer) {
                issuer->notifyWalkerDestruction(date);
            }
            if (canGenerateWalkersUntil < date) {
                randomWalkers->init(date);
            }
            canGenerateWalkersUntil = date;
            canGenerateWalkersUntil.add(conf->getRandomWalkerGenerationInterval() * 10);
        });

        return true;
    }

    return false;
}
