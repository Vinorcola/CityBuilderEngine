#include "CityEntryPoint.hpp"

#include "src/engine/element/dynamic/Character.hpp"
#include "src/engine/element/static/behavior/QueuedWalkerGenerator.hpp"
#include "src/engine/random.hpp"
#include "src/global/conf/CharacterInformation.hpp"



CityEntryPoint::CityEntryPoint(
    QObject* parent,
    const BuildingInformation* conf,
    const MapCoordinates& coordinates
) :
    ProcessableBuilding(parent, conf, MapArea(coordinates), coordinates),
    immigrantGenerator()
{
    // TODO: Disable for now. To review.
//    for (auto behavior : getBehaviors()) {
//        auto queuedWalkerGenerator(dynamic_cast<QueuedWalkerGenerator*>(behavior));
//        if (queuedWalkerGenerator && queuedWalkerGenerator->getWalkerConf()->getKey() == "immigrant") {
//            immigrantGenerator = queuedWalkerGenerator;
//            break;
//        }
//    }
}



void CityEntryPoint::requestImmigrant(std::function<void(Character*)> onWalkerCreation)
{
    immigrantGenerator->registerWalkerRequest(onWalkerCreation);
}



void CityEntryPoint::process(const CycleDate& /*date*/)
{

}



bool CityEntryPoint::processInteraction(const CycleDate& /*date*/, Character* /*actor*/)
{
    return false;
}
