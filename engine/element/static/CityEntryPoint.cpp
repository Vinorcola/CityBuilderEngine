#include "CityEntryPoint.hpp"

#include "engine/element/dynamic/Character.hpp"
#include "engine/element/static/behavior/QueuedWalkerGenerator.hpp"
#include "engine/random.hpp"
#include "global/conf/CharacterInformation.hpp"



CityEntryPoint::CityEntryPoint(
    QObject* parent,
    const BehaviorFactory* behaviorFactory,
    const StaticElementInformation* conf,
    const MapCoordinates& coordinates
) :
    ProcessableBuilding(parent, behaviorFactory, conf, MapArea(coordinates), coordinates),
    immigrantGenerator()
{
    for (auto behavior : getBehaviors()) {
        auto queuedWalkerGenerator(dynamic_cast<QueuedWalkerGenerator*>(behavior));
        if (queuedWalkerGenerator && queuedWalkerGenerator->getWalkerConf()->getKey() == "immigrant") {
            immigrantGenerator = queuedWalkerGenerator;
            break;
        }
    }
}



void CityEntryPoint::requestImmigrant(std::function<void(Character*)> onWalkerCreation)
{
    immigrantGenerator->registerWalkerRequest(onWalkerCreation);
}
