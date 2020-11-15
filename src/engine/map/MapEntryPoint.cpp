#include "MapEntryPoint.hpp"

#include <QtCore/QException>
#include <QtCore/QRandomGenerator>

#include "src/engine/element/dynamic/character/ImmigrantCharacter.hpp"
#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"
#include "src/engine/element/static/building/HouseBuilding.hpp"



MapEntryPoint::MapEntryPoint(
    QObject* parent,
    CharacterFactoryInterface& characterFactory,
    const BuildingInformation& conf,
    const MapCoordinates& location,
    const CharacterInformation& immigrantConf
) :
    AbstractProcessableBuilding(parent, conf, MapArea(location), location),
    characterFactory(characterFactory),
    immigrantConf(immigrantConf),
    nextImmigrantGenerationDate(),
    immigrantRequestQueue()
{

}



void MapEntryPoint::requestImmigrant(HouseBuilding& requester)
{
    immigrantRequestQueue.append(&requester);
}



void MapEntryPoint::process(const CycleDate& date)
{
    if (immigrantRequestQueue.isEmpty()) {
        return;
    }

    if (date == nextImmigrantGenerationDate) {
        QPointer<AbstractProcessableBuilding> issuer;
        do {
            issuer = immigrantRequestQueue.takeFirst();
        } while (issuer.isNull() && !immigrantRequestQueue.isEmpty());
        if (issuer.isNull()) {
            // No more valid issuers.
            return;
        }

        characterFactory.generateImmigrant(immigrantConf, *this, *issuer);
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
