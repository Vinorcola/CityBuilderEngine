#include "CivilianEntryPoint.hpp"

#include <QtCore/QException>
#include <QtCore/QRandomGenerator>

#include "src/engine/map/dynamicElement/character/ImmigrantCharacter.hpp"
#include "src/engine/map/dynamicElement/CharacterGeneratorInterface.hpp"
#include "src/engine/map/staticElement/building/HouseBuilding.hpp"



CivilianEntryPoint::CivilianEntryPoint(
    CharacterGeneratorInterface& characterFactory,
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile,
    const CharacterInformation& immigrantConf
) :
    AbstractProcessableBuilding(conf, area, orientation, entryPointTile),
    characterFactory(characterFactory),
    immigrantConf(immigrantConf),
    nextImmigrantGenerationCountDown(),
    immigrantRequestQueue()
{
    // IMPORTANT: characterFactory is not initialized yet within constructor scope!
    setupNextImmigrantGenerationDate();
}



QSharedPointer<CivilianEntryPoint> CivilianEntryPoint::Create(
    CharacterGeneratorInterface& characterFactory,
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile,
    const CharacterInformation& immigrantConf
) {
    // IMPORTANT: characterFactory is not initialized yet within constructor scope!
    auto entryPoint(new CivilianEntryPoint(characterFactory, conf, area, orientation, entryPointTile, immigrantConf));
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
    nextImmigrantGenerationCountDown = QRandomGenerator::global()->bounded(
        MIN_IMMIGRANT_GENERATION_INTERVAL,
        MAX_IMMIGRANT_GENERATION_INTERVAL + 1
    );
}
