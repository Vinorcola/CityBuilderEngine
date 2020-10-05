#include "MapEntryPoint.hpp"

#include <QtCore/QException>
#include <QtCore/QRandomGenerator>

#include "src/engine/element/dynamic/character/ImmigrantCharacter.hpp"
#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"



MapEntryPoint::MapEntryPoint(
    CharacterFactoryInterface& characterFactory,
    const MapCoordinates& location,
    const CharacterInformation& immigrantConf
) :
    characterFactory(characterFactory),
    location(location),
    immigrantConf(immigrantConf),
    nextImmigrantGenerationDate(),
    immigrantRequestQueue()
{

}



void MapEntryPoint::requestImmigrant(ProcessableBuilding& issuer)
{
    immigrantRequestQueue.append(&issuer);
}



void MapEntryPoint::process(const CycleDate& date)
{
    if (immigrantRequestQueue.isEmpty()) {
        return;
    }

    if (date == nextImmigrantGenerationDate) {
        QPointer<ProcessableBuilding> issuer;
        do {
            issuer = immigrantRequestQueue.takeFirst();
        } while (issuer.isNull() && !immigrantRequestQueue.isEmpty());
        if (issuer.isNull()) {
            // No more valid issuers.
            return;
        }

        characterFactory.generateImmigrant(immigrantConf, location, *issuer);
        setupNextImmigrantGenerationDate(date);
    } else if (date > nextImmigrantGenerationDate) {
        setupNextImmigrantGenerationDate(date);
    }
}



void MapEntryPoint::setupNextImmigrantGenerationDate(const CycleDate& currentDate)
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
