#include "HouseBuilding.hpp"

#include "src/engine/city/PopulationRegisterInterface.hpp"
#include "src/engine/element/dynamic/character/ImmigrantCharacter.hpp"
#include "src/engine/element/dynamic/CharacterFactoryInterface.hpp"
#include "src/engine/element/static/building/ImmigrantGeneratorInterface.hpp"
#include "src/global/conf/BuildingInformation.hpp"



HouseBuilding::HouseBuilding(
    QObject* parent,
    ImmigrantGeneratorInterface& immigrantGenerator,
    PopulationRegisterInterface& populationRegister,
    const BuildingInformation& conf,
    const MapArea& area,
    const MapCoordinates& entryPoint
) :
    ProcessableBuilding(parent, conf, area, entryPoint),
    immigrantGenerator(immigrantGenerator),
    populationRegister(populationRegister),
    inhabitants(0)
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
        int inhabitantsDelta(qMin(
            conf.getHouseConf().populationPerImmigrant,
            conf.getHouseConf().populationCapacity - inhabitants
        ));
        inhabitants += inhabitantsDelta;
        populationRegister.registerPopulation(inhabitantsDelta);

        if (inhabitants < conf.getHouseConf().populationCapacity) {
            immigrantGenerator.requestImmigrant(*this);
        }

        return true;
    }

    return false;
}
