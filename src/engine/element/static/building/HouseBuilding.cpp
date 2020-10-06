#include "HouseBuilding.hpp"

#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"
#include "src/engine/element/dynamic/character/ImmigrantCharacter.hpp"
#include "src/engine/map/MapEntryPoint.hpp"
#include "src/global/conf/BuildingInformation.hpp"



HouseBuilding::HouseBuilding(
    QObject* parent,
    CharacterFactoryInterface& characterFactory,
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint,
    MapEntryPoint& immigrantGenerator
) :
    ProcessableBuilding(parent, conf, area, entryPoint),
    characterFactory(characterFactory),
    immigrantGenerator(immigrantGenerator),
    population(0)
{

}



void HouseBuilding::init(const CycleDate& /*date*/)
{
    immigrantGenerator.requestImmigrant(*this);
}



void HouseBuilding::process(const CycleDate& /*date*/)
{

}



bool HouseBuilding::processInteraction(const CycleDate& /*date*/, Character& actor)
{
    auto immigrant(dynamic_cast<ImmigrantCharacter*>(&actor));
    if (immigrant) {
        population = qMin(population + conf.getHouseConf().populationPerImmigrant, conf.getHouseConf().populationCapacity);
        if (population < conf.getHouseConf().populationCapacity) {
            immigrantGenerator.requestImmigrant(*this);
        }
        characterFactory.clearCharacter(actor);

        return true;
    }

    return false;
}
