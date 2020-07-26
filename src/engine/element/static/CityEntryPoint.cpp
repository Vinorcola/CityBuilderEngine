#include "CityEntryPoint.hpp"

#include "src/engine/element/dynamic/Character.hpp"
#include "src/engine/element/static/behavior/QueuedWalkerGenerator.hpp"
#include "src/engine/random.hpp"
#include "src/global/conf/CharacterInformation.hpp"



CityEntryPoint::CityEntryPoint(
    QObject* parent,
    const BehaviorFactory* behaviorFactory,
    const BuildingInformation* conf,
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
