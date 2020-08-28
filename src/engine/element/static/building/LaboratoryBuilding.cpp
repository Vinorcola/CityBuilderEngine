#include "LaboratoryBuilding.hpp"

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
    characterFactory(characterFactory)
{

}



void LaboratoryBuilding::process(const CycleDate& date)
{

}



bool LaboratoryBuilding::processInteraction(const CycleDate& date, Character& actor)
{
    if (actor.isOfType(conf.getLaboratoryConf().acceptedStudent)) {
        characterFactory.clearCharacter(actor);

        return true;
    }

    return false;
}
