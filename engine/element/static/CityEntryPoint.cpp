#include "CityEntryPoint.hpp"

#include "engine/element/dynamic/TargetedWalker.hpp"
#include "engine/element/static/behavior/QueuedWalkerGenerator.hpp"
#include "engine/random.hpp"
#include "global/conf/DynamicElementInformation.hpp"

const int IMMIGRANT_MIN_INTERVAL(10);
const int IMMIGRANT_MAX_INTERVAL(60);



CityEntryPoint::CityEntryPoint(
    QObject* parent,
    const BehaviorFactory* behaviorFactory,
    const StaticElementInformation* conf,
    const MapCoordinates& coordinates
) :
    Building(parent, behaviorFactory, conf, MapArea(coordinates), coordinates),
    immigrantGenerator()
{
    for (auto behavior : behaviors) {
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
