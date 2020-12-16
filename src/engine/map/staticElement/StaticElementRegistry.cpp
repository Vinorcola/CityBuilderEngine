#include "StaticElementRegistry.hpp"

#include <cassert>

#include "src/engine/city/WorkingPlaceRegistryInterface.hpp"
#include "src/engine/map/staticElement/building/CivilianEntryPoint.hpp"
#include "src/engine/map/staticElement/natureElement/NatureElement.hpp"
#include "src/exceptions/UnexpectedException.hpp"
#include "src/global/conf/BuildingInformation.hpp"



StaticElementRegistry::StaticElementRegistry(
    CharacterGeneratorInterface& characterGenerator,
    PopulationRegistryInterface& populationRegistry,
    WorkingPlaceRegistryInterface& workingPlaceRegistry,
    PathGeneratorInterface& pathGenerator,
    CivilianEntryPoint& civilianEntryPoint
) :
    workingPlaceRegistry(workingPlaceRegistry),
    buildingSearchEngine(),
    natureElementSearchEngine(pathGenerator),
    factory(characterGenerator, civilianEntryPoint, populationRegistry, buildingSearchEngine, natureElementSearchEngine),
    buildings(),
    natureElements(),
    processableElements()
{
    // IMPORTANT: characterGenerator is not initialized yet within constructor scope!
}



const BuildingSearchEngine& StaticElementRegistry::getBuildingSearchEngine() const
{
    return buildingSearchEngine;
}



void StaticElementRegistry::generateBuilding(
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation
) {
    QSharedPointer<AbstractBuilding> building;
    switch (conf.getType()) {
        case BuildingInformation::Type::Road: {
            building = factory.generateRoad(conf, area, orientation);
            break;
        }

        default:
            throw UnexpectedException("Cannot create non-processable building of type " + conf.getTitle() + ".");
    }

    assert(!building.isNull());
    buildings.insert(building.get(), building);
}



void StaticElementRegistry::generateProcessableBuilding(
    const BuildingInformation& conf,
    const TileArea& area,
    Direction orientation,
    const TileCoordinates& entryPoint
) {
    QSharedPointer<AbstractProcessableBuilding> building;
    switch (conf.getType()) {
        case BuildingInformation::Type::Farm:
            building = factory.generateFarm(conf, area, orientation, entryPoint);
            break;

        case BuildingInformation::Type::House:
            building = factory.generateHouse(conf, area, orientation, entryPoint);
            break;

        case BuildingInformation::Type::Laboratory:
            building = factory.generateLaboratory(conf, area, orientation, entryPoint);
            buildingSearchEngine.registerBuilding(building);
            break;

        case BuildingInformation::Type::Producer:
            building = factory.generateProducer(conf, area, orientation, entryPoint);
            break;

        case BuildingInformation::Type::Sanity:
            building = factory.generateSanity(conf, area, orientation, entryPoint);
            break;

        case BuildingInformation::Type::School:
            building = factory.generateSchool(conf, area, orientation, entryPoint);
            break;

        case BuildingInformation::Type::Storage: {
            auto storageBuilding(factory.generateStorage(conf, area, orientation, entryPoint));
            building = storageBuilding;
            buildingSearchEngine.registerStorageBuilding(storageBuilding);
            break;
        }

        default:
            throw UnexpectedException("Cannot create processable building of type " + conf.getTitle() + ".");
    }

    assert(!building.isNull());
    buildings.insert(building.get(), building);
    processableElements.insert(building.get(), building);
    if (conf.getMaxWorkers() > 0) {
        workingPlaceRegistry.registerWorkingPlace(building);
    }
}



void StaticElementRegistry::generateNatureElement(const NatureElementInformation& conf, const TileArea& area)
{
    QSharedPointer<NatureElement> natureElement(new NatureElement(conf, area));
    natureElements.insert(natureElement.get(), natureElement);
    natureElementSearchEngine.registerRawMaterial(conf, area);

    // Note: For now, we do not have processable nature elements. But trees will typically become processable in order
    // to grow after cutting.
}



QList<BuildingState> StaticElementRegistry::getBuildingsState() const
{
    QList<BuildingState> list;
    for (auto building : buildings) {
        list.append(building->getCurrentState());
    }

    return list;
}



QList<NatureElementState> StaticElementRegistry::getNatureElementsState() const
{
    QList<NatureElementState> list;
    for (auto natureElement : natureElements) {
        list.append(natureElement->getState());
    }

    return list;
}



void StaticElementRegistry::process(const CycleDate& date)
{
    for (auto processableElement : processableElements) {
        processableElement->process(date);
    }
}
