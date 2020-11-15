#include "CivilianEntryPoint.hpp"

#include <QtCore/QException>
#include <QtCore/QRandomGenerator>

#include "src/engine/element/dynamic/character/ImmigrantCharacter.hpp"
#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"
#include "src/engine/element/static/building/HouseBuilding.hpp"



CivilianEntryPoint::CivilianEntryPoint(
    CharacterFactoryInterface& characterFactory,
    const BuildingInformation& conf,
    const MapCoordinates& location,
    const CharacterInformation& immigrantConf
) :
    AbstractProcessableBuilding(conf, MapArea(location), location),
    characterFactory(characterFactory),
    immigrantConf(immigrantConf),
    nextImmigrantGenerationDate(),
    immigrantRequestQueue()
{

}



void CivilianEntryPoint::requestImmigrant(HouseBuilding& requester)
{
    immigrantRequestQueue.append(requester.getReference<HouseBuilding>());
}



void CivilianEntryPoint::process(const CycleDate& date)
{
    if (immigrantRequestQueue.isEmpty()) {
        return;
    }

    if (date == nextImmigrantGenerationDate) {
        do {
            auto issuer(immigrantRequestQueue.takeFirst());
            if (!issuer.isValid()) {
                continue;
            }

            characterFactory.generateImmigrant(immigrantConf, *this, issuer.get());
            setupNextImmigrantGenerationDate(date);
        } while (!immigrantRequestQueue.isEmpty());
    } else if (date > nextImmigrantGenerationDate) {
        setupNextImmigrantGenerationDate(date);
    }
}



void CivilianEntryPoint::setupNextImmigrantGenerationDate(const CycleDate& currentDate)
{
    if (immigrantRequestQueue.isEmpty()) {
        return;
    }

    if (nextImmigrantGenerationDate <= currentDate) {
        nextImmigrantGenerationDate.reassign(
            currentDate,
            QRandomGenerator::global()->bounded(MIN_IMMIGRANT_GENERATION_INTERVAL, MAX_IMMIGRANT_GENERATION_INTERVAL + 1)
        );
    }
}
