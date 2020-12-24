#include "StaticElementFactory.hpp"

#include "src/engine/map/staticElement/building/CivilianEntryPoint.hpp"
#include "src/engine/map/staticElement/building/FarmBuilding.hpp"
#include "src/engine/map/staticElement/building/HouseBuilding.hpp"
#include "src/engine/map/staticElement/building/IndustrialBuilding.hpp"
#include "src/engine/map/staticElement/building/LaboratoryBuilding.hpp"
#include "src/engine/map/staticElement/building/ProducerBuilding.hpp"
#include "src/engine/map/staticElement/building/Road.hpp"
#include "src/engine/map/staticElement/building/SanityBuilding.hpp"
#include "src/engine/map/staticElement/building/SchoolBuilding.hpp"
#include "src/engine/map/staticElement/building/StorageBuilding.hpp"



StaticElementFactory::StaticElementFactory(
    CharacterGeneratorInterface& characterGenerator,
    ImmigrantGeneratorInterface& immigrantGenerator,
    PopulationRegistryInterface& populationRegister,
    const BuildingSearchEngine& buildingSearchEngine,
    const NatureElementSearchEngine& natureElementSearchEngine
) :
    characterGenerator(characterGenerator),
    immigrantGenerator(immigrantGenerator),
    populationRegister(populationRegister),
    buildingSearchEngine(buildingSearchEngine),
    natureElementSearchEngine(natureElementSearchEngine)
{

}



QSharedPointer<AbstractProcessableBuilding> StaticElementFactory::generateFarm(
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) {
    return FarmBuilding::Create(characterGenerator, conf, area, orientation, entryPointTile);
}



QSharedPointer<AbstractProcessableBuilding> StaticElementFactory::generateHouse(
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) {
    return HouseBuilding::Create(immigrantGenerator, populationRegister, conf, area, orientation, entryPointTile);
}



QSharedPointer<AbstractStoringBuilding> StaticElementFactory::generateIndustrial(
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) {
    return IndustrialBuilding::Create(characterGenerator, conf, area, orientation, entryPointTile);
}



QSharedPointer<AbstractProcessableBuilding> StaticElementFactory::generateLaboratory(
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) {
    return LaboratoryBuilding::Create(characterGenerator, conf, area, orientation, entryPointTile);
}



QSharedPointer<AbstractProcessableBuilding> StaticElementFactory::generateProducer(
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) {
    return ProducerBuilding::Create(natureElementSearchEngine, characterGenerator, conf, area, orientation, entryPointTile);
}



QSharedPointer<AbstractBuilding> StaticElementFactory::generateRoad(
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation
) {
    return QSharedPointer<AbstractBuilding>(new Road(conf, area, orientation));
}



QSharedPointer<AbstractProcessableBuilding> StaticElementFactory::generateSanity(
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) {
    return SanityBuilding::Create(characterGenerator, conf, area, orientation, entryPointTile);
}



QSharedPointer<AbstractProcessableBuilding> StaticElementFactory::generateSchool(
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) {
    return SchoolBuilding::Create(buildingSearchEngine, characterGenerator, conf, area, orientation, entryPointTile);
}



QSharedPointer<AbstractStoringBuilding> StaticElementFactory::generateStorage(
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const Tile& entryPointTile
) {
    return StorageBuilding::Create(conf, area, orientation, entryPointTile);
}
