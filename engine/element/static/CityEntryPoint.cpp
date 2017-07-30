#include "CityEntryPoint.hpp"

#include "engine/random.hpp"
#include "defines.hpp"

const int IMMIGRANT_MIN_INTERVAL(10);
const int IMMIGRANT_MAX_INTERVAL(60);



CityEntryPoint::CityEntryPoint(QObject* parent, const MapCoordinates& coordinates) :
    AbstractProcessableStaticMapElement(parent, MapArea(coordinates), coordinates),
    nextImmigrantGenerationDate(),
    immigrantRequestQueue()
{

}



void CityEntryPoint::process(const CycleDate& date)
{
    if (!immigrantRequestQueue.isEmpty()) {
        if (date == nextImmigrantGenerationDate) {
            emit requestDynamicElementCreation(
                AbstractDynamicMapElement::Type::Immigrant,
                0,
    #ifdef SLOW_MOTION
                0.25 / CYCLE_PER_SECOND,
    #else
                2.0 / CYCLE_PER_SECOND,
    #endif
                immigrantRequestQueue.takeFirst()
            );
            setupNextImmigrantGenerationDate(date);
        } else if (date > nextImmigrantGenerationDate) {
            setupNextImmigrantGenerationDate(date);
        }
    }
}



void CityEntryPoint::processInteraction(const CycleDate& /*date*/, AbstractDynamicMapElement* /*actor*/)
{

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
        nextImmigrantGenerationDate = currentDate;
        nextImmigrantGenerationDate.add(randomInt(IMMIGRANT_MIN_INTERVAL, IMMIGRANT_MAX_INTERVAL));
    }
}
