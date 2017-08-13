#include "ServiceBuilding.hpp"

#include "engine/map/Map.hpp"



ServiceBuilding::ServiceBuilding(
    QObject* parent,
    const StaticElementInformation* conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    AbstractProcessableStaticMapElement(parent, conf, area, entryPoint),
    randomWalkers(conf->getRandomWalkerConf() ?
        new RandomWalkerGenerator(
            this,
            conf->getRandomWalkerConf(),
            conf->getRandomWalkerGenerationInterval(),
            conf->getMaxNumberOfRandomWalkers()
        ) :
        nullptr
    )
{
    if (randomWalkers) {
        connect(randomWalkers, &RandomWalkerGenerator::requestDynamicElementCreation, this, &ServiceBuilding::requestDynamicElementCreation);
        connect(randomWalkers, &RandomWalkerGenerator::requestDynamicElementDestruction, this, &ServiceBuilding::requestDynamicElementDestruction);
    }
}



void ServiceBuilding::init(const CycleDate& date)
{
    if (randomWalkers) {
        randomWalkers->init(date);
        if (getEntryPoint().isValid()) {
            randomWalkers->setGenerationSpeedRatio(1.0, date);
        }
    }
}



void ServiceBuilding::process(const CycleDate& date)
{
    if (randomWalkers) {
        randomWalkers->process(date);
    }
}



bool ServiceBuilding::processInteraction(const CycleDate& date, AbstractDynamicMapElement* actor)
{
    if (randomWalkers && randomWalkers->processInteraction(date, actor)) {
        return true;
    }

    return false;
}
