#include "CityEntryPoint.hpp"

#include "engine/random.hpp"

const int IMMIGRANT_MIN_INTERVAL(10);
const int IMMIGRANT_MAX_INTERVAL(60);



CityEntryPoint::CityEntryPoint(
    QObject* parent,
    const StaticElementInformation* conf,
    const MapCoordinates& coordinates,
    const DynamicElementInformation* immigrantConf
) : AbstractProcessableStaticMapElement(parent, conf, MapArea(coordinates), coordinates),
    immigrantConf(immigrantConf),
    nextImmigrantGenerationDate(),
    immigrantRequestQueue()
{

}



void CityEntryPoint::process(const CycleDate& date)
{
    if (!immigrantRequestQueue.isEmpty()) {
        if (date == nextImmigrantGenerationDate) {
            emit requestDynamicElementCreation(
                immigrantConf,
                immigrantRequestQueue.takeFirst()
            );
            setupNextImmigrantGenerationDate(date);
        } else if (date > nextImmigrantGenerationDate) {
            setupNextImmigrantGenerationDate(date);
        }
    }
}



bool CityEntryPoint::processInteraction(const CycleDate& /*date*/, AbstractDynamicMapElement* /*actor*/)
{
    return false;
}



void CityEntryPoint::registerImmigrantRequest(AbstractProcessableStaticMapElement* issuer, std::function<void(TargetedWalker*)> onImmigrantCreation)
{
    immigrantRequestQueue.append([issuer, onImmigrantCreation](AbstractDynamicMapElement* element) {
        auto immigrant(static_cast<TargetedWalker*>(element));
        immigrant->assignTarget(issuer);
        onImmigrantCreation(immigrant);
    });
}



void CityEntryPoint::setupNextImmigrantGenerationDate(const CycleDate& currentDate)
{
    if (!immigrantRequestQueue.isEmpty() && nextImmigrantGenerationDate <= currentDate) {
        nextImmigrantGenerationDate.reassign(currentDate, randomInt(IMMIGRANT_MIN_INTERVAL, IMMIGRANT_MAX_INTERVAL));
    }
}
