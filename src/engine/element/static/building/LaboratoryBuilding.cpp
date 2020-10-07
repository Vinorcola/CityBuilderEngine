#include "LaboratoryBuilding.hpp"

#include "src/engine/element/dynamic/character/WanderingCharacter.hpp"
#include "src/engine/element/dynamic/Character.hpp"
#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"
#include "src/global/conf/BuildingInformation.hpp"



LaboratoryBuilding::LaboratoryBuilding(
    QObject* parent,
    CharacterFactoryInterface& characterFactory,
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    ProcessableBuilding(parent, conf, area, entryPoint),
    characterFactory(characterFactory),
    walkerGenerationLimitDate(),
    scientist(),
    nextWalkerGenerationDate()
{

}



void LaboratoryBuilding::process(const CycleDate& date)
{
    if (!walkerGenerationLimitDate || date > walkerGenerationLimitDate) {
        return;
    }

    if (nextWalkerGenerationDate) {
        if (date < nextWalkerGenerationDate) {
            return;
        }

        scientist = &characterFactory.generateWanderingCharacter(conf.getLaboratoryConf().emittedScientist.conf, *this);

        if (canGenerateNewWalker()) {
            setupNextWalkerGenerationDate(date);
        }
        else {
            nextWalkerGenerationDate.reset();
        }
    }
    else if (canGenerateNewWalker()) {
        setupNextWalkerGenerationDate(date);
    }
}



bool LaboratoryBuilding::processInteraction(const CycleDate& date, Character& actor)
{
    if (&actor == scientist) {
        scientist.clear();

        return true;
    }

    if (actor.isOfType(conf.getLaboratoryConf().acceptedStudent)) {
        walkerGenerationLimitDate.reassign(date, conf.getLaboratoryConf().producingInterval);

        return true;
    }

    return false;
}



bool LaboratoryBuilding::canGenerateNewWalker() const
{
    return scientist.isNull();
}



void LaboratoryBuilding::setupNextWalkerGenerationDate(const CycleDate& date)
{
    nextWalkerGenerationDate.reassign(date, conf.getLaboratoryConf().emittedScientist.generationInterval);
}
