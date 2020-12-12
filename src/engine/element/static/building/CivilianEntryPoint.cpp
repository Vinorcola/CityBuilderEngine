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
    AbstractProcessableBuilding(conf, MapArea(location), Direction::West, location),
    characterFactory(characterFactory),
    immigrantConf(immigrantConf),
    nextImmigrantGenerationCountDown(),
    immigrantRequestQueue()
{

}



QSharedPointer<CivilianEntryPoint> CivilianEntryPoint::Create(
    CharacterFactoryInterface& characterFactory,
    const BuildingInformation& conf,
    const MapCoordinates& location,
    const CharacterInformation& immigrantConf
) {
    auto entryPoint(new CivilianEntryPoint(characterFactory, conf, location, immigrantConf));
    QSharedPointer<CivilianEntryPoint> pointer(entryPoint);
    entryPoint->selfReference = pointer;

    return pointer;
}



void CivilianEntryPoint::requestImmigrant(const QWeakPointer<AbstractProcessableBuilding>& requester)
{
    immigrantRequestQueue.append(requester);
}



void CivilianEntryPoint::process(const CycleDate& /*date*/)
{
    if (immigrantRequestQueue.isEmpty()) {
        return;
    }

    --nextImmigrantGenerationCountDown;
    if (nextImmigrantGenerationCountDown <= 0) {
        do {
            auto issuer(immigrantRequestQueue.takeFirst().toStrongRef());
            if (issuer) {
                characterFactory.generateImmigrant(immigrantConf, selfReference, issuer->getSelfReference());
                setupNextImmigrantGenerationDate();
                break;
            }
        } while (!immigrantRequestQueue.isEmpty());
    }
}



void CivilianEntryPoint::setupNextImmigrantGenerationDate()
{
    if (immigrantRequestQueue.isEmpty()) {
        return;
    }

    if (nextImmigrantGenerationCountDown <= 0) {
        nextImmigrantGenerationCountDown = QRandomGenerator::global()->bounded(
            MIN_IMMIGRANT_GENERATION_INTERVAL,
            MAX_IMMIGRANT_GENERATION_INTERVAL + 1
        );
    }
}
