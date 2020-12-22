#include "HouseBuilding.hpp"

#include "src/engine/city/PopulationRegistryInterface.hpp"
#include "src/engine/map/dynamicElement/character/ImmigrantCharacter.hpp"
#include "src/engine/map/dynamicElement/CharacterGeneratorInterface.hpp"
#include "src/engine/map/staticElement/building/ImmigrantGeneratorInterface.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/state/BuildingState.hpp"



HouseBuilding::HouseBuilding(
    ImmigrantGeneratorInterface& immigrantGenerator,
    PopulationRegistryInterface& populationRegister,
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) :
    AbstractProcessableBuilding(conf, area, orientation, entryPointTile),
    immigrantGenerator(immigrantGenerator),
    populationRegister(populationRegister),
    inhabitants(0),
    hasRequestedInhabitants(false)
{

}



QSharedPointer<AbstractProcessableBuilding> HouseBuilding::Create(
    ImmigrantGeneratorInterface& immigrantGenerator,
    PopulationRegistryInterface& populationRegister,
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) {
    auto house(new HouseBuilding(immigrantGenerator, populationRegister, conf, area, orientation, entryPointTile));
    QSharedPointer<AbstractProcessableBuilding> pointer(house);
    house->selfReference = pointer;

    return pointer;
}



void HouseBuilding::process(const CycleDate& /*date*/)
{
    if (!hasRequestedInhabitants && inhabitants < conf.getHouseConf().populationCapacity) {
        immigrantGenerator.requestImmigrant(selfReference);
        hasRequestedInhabitants = true;
    }
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
            immigrantGenerator.requestImmigrant(selfReference);
        }
        else {
            hasRequestedInhabitants = false;
        }

        return true;
    }

    return false;
}



BuildingState HouseBuilding::getCurrentState() const
{
    return BuildingState::CreateHouseState(
        reinterpret_cast<qintptr>(this),
        conf,
        area,
        orientation,
        getCurrentStatus(),
        getCurrentWorkerQuantity(),
        stateVersion,
        inhabitants
    );
}
