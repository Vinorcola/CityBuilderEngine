#include "StaticElementFactory.hpp"

#include "src/engine/map/staticElement/building/CivilianEntryPoint.hpp"
#include "src/engine/map/staticElement/building/FarmBuilding.hpp"
#include "src/engine/map/staticElement/building/HouseBuilding.hpp"
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
    const MapArea& area,
    Direction orientation,
    const MapCoordinates& entryPoint
) {
    return FarmBuilding::Create(characterGenerator, conf, area, orientation, entryPoint);
}



QSharedPointer<AbstractProcessableBuilding> StaticElementFactory::generateHouse(
    const BuildingInformation& conf,
    const MapArea& area,
    Direction orientation,
    const MapCoordinates& entryPoint
) {
    return HouseBuilding::Create(immigrantGenerator, populationRegister, conf, area, orientation, entryPoint);
}



QSharedPointer<AbstractProcessableBuilding> StaticElementFactory::generateLaboratory(
    const BuildingInformation& conf,
    const MapArea& area,
    Direction orientation,
    const MapCoordinates& entryPoint
) {
    return LaboratoryBuilding::Create(characterGenerator, conf, area, orientation, entryPoint);
}



QSharedPointer<AbstractProcessableBuilding> StaticElementFactory::generateProducer(
    const BuildingInformation& conf,
    const MapArea& area,
    Direction orientation,
    const MapCoordinates& entryPoint
) {
    return ProducerBuilding::Create(natureElementSearchEngine, characterGenerator, conf, area, orientation, entryPoint);
}



QSharedPointer<AbstractBuilding> StaticElementFactory::generateRoad(
    const BuildingInformation& conf,
    const MapArea& area,
    Direction orientation
) {
    return QSharedPointer<AbstractBuilding>(new Road(conf, area, orientation));
}



QSharedPointer<AbstractProcessableBuilding> StaticElementFactory::generateSanity(
    const BuildingInformation& conf,
    const MapArea& area,
    Direction orientation,
    const MapCoordinates& entryPoint
) {
    return SanityBuilding::Create(characterGenerator, conf, area, orientation, entryPoint);
}



QSharedPointer<AbstractProcessableBuilding> StaticElementFactory::generateSchool(
    const BuildingInformation& conf,
    const MapArea& area,
    Direction orientation,
    const MapCoordinates& entryPoint
) {
    return SchoolBuilding::Create(buildingSearchEngine, characterGenerator, conf, area, orientation, entryPoint);
}



QSharedPointer<StorageBuilding> StaticElementFactory::generateStorage(
    const BuildingInformation& conf,
    const MapArea& area,
    Direction orientation,
    const MapCoordinates& entryPoint
) {
    return StorageBuilding::Create(conf, area, orientation, entryPoint);
}
