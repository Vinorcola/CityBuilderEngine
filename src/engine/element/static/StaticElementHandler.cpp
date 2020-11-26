#include "StaticElementHandler.hpp"

#include <QtCore/QDebug>
#include <QtCore/QtAlgorithms>

#include "src/engine/city/PopulationHandler.hpp"
#include "src/engine/element/static/building/AbstractBuilding.hpp"
#include "src/engine/element/static/building/CivilianEntryPoint.hpp"
#include "src/engine/element/static/building/FarmBuilding.hpp"
#include "src/engine/element/static/building/HouseBuilding.hpp"
#include "src/engine/element/static/building/LaboratoryBuilding.hpp"
#include "src/engine/element/static/building/ProducerBuilding.hpp"
#include "src/engine/element/static/building/Road.hpp"
#include "src/engine/element/static/building/SanityBuilding.hpp"
#include "src/engine/element/static/building/SchoolBuilding.hpp"
#include "src/engine/element/static/building/StorageBuilding.hpp"
#include "src/engine/element/static/natureElement/NatureElement.hpp"
#include "src/engine/map/Map.hpp"
#include "src/engine/processing/TimeCycleProcessor.hpp"
#include "src/engine/state/BuildingState.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/global/conf/NatureElementInformation.hpp"



StaticElementHandler::State::State(
    CharacterFactoryInterface& characterFactory,
    const Conf& conf,
    const MapCoordinates& entryPointLocation
) :
    entryPoint(CivilianEntryPoint::Create(
        characterFactory,
        conf.getBuildingConf("mapEntryPoint"),
        entryPointLocation,
        conf.getCharacterConf("immigrant")
    )),
    buildings(),
    natureElements()
{

}



StaticElementHandler::StaticElementHandler(
    PopulationHandler& populationHandler,
    TimeCycleProcessor& processor,
    const Map& map,
    CharacterFactoryInterface& characterFactory,
    const Conf& conf,
    const MapCoordinates& mapEntryPointLocation
) :
    MapDetailsInterface(),
    populationHandler(populationHandler),
    processor(processor),
    map(map),
    characterFactory(characterFactory),
    currentState(characterFactory, conf, mapEntryPointLocation),
    detailsCache(),
    pathGenerator(*this),
    buildingSearchEngine(),
    natureElementSearchEngine(pathGenerator)
{
    processor.registerBuilding(currentState.entryPoint);
}



const PathGenerator& StaticElementHandler::getPathGenerator() const
{
    return pathGenerator;
}



const BuildingSearchEngine& StaticElementHandler::getBuildingSearchEngine() const
{
    return buildingSearchEngine;
}



const NatureElementSearchEngine& StaticElementHandler::getNatureElementSearchEngine() const
{
    return natureElementSearchEngine;
}



bool StaticElementHandler::isLocationConstructible(const MapCoordinates& location) const
{
    return
        map.isLocationValid(location) &&
        !detailsCache.nonConstructibleCoordinates.contains(location.getHash());
}



bool StaticElementHandler::isAreaConstructible(const MapArea& area) const
{
    for (auto coordinates : area) {
        if (!isLocationConstructible(coordinates)) {
            return false;
        }
    }

    return true;
}



bool StaticElementHandler::isLocationTraversable(const MapCoordinates& location) const
{
    return
        map.isLocationValid(location) &&
        !detailsCache.nonTraversableCoordinates.contains(location.getHash());
}



bool StaticElementHandler::hasRoadAtLocation(const MapCoordinates& location) const
{
    return detailsCache.roadCoordinates.contains(location.getHash());
}



bool StaticElementHandler::canConstructRoadAtLocation(const MapCoordinates& location) const
{
    return
        map.isLocationValid(location) && (
            isLocationConstructible(location) ||
            hasRoadAtLocation(location)
        );
}



QList<BuildingState> StaticElementHandler::getBuildingsState() const
{
    QList<BuildingState> list;
    for (auto element : currentState.buildings) {
        list.append(element->getCurrentState());
    }

    return list;
}



QList<NatureElementState> StaticElementHandler::getNatureElementsState() const
{
    QList<NatureElementState> list;
    for (auto element : currentState.natureElements) {
        list.append(element->getState());
    }

    return list;
}



void StaticElementHandler::createBuilding(const BuildingInformation& conf, const MapArea& area)
{
    if (!isAreaConstructible(area)) {
        qDebug() << "WARNING: Try to create a building on an accupyed area " + area.toString() + ". Skipping the creation.";
        return;
    }
    if (area.getSize() != conf.getSize()) {
        qDebug() << "WARNING: Selected area size does not match the building size. Skipping the creation.";
        return;
    }

    switch (conf.getType()) {
        case BuildingInformation::Type::Farm:
            generateFarm(conf, area);
            break;

        case BuildingInformation::Type::House:
            generateHouse(conf, area);
            break;

        case BuildingInformation::Type::Laboratory:
            generateLaboratory(conf, area);
            break;

        case BuildingInformation::Type::Producer:
            generateProducer(conf, area);
            break;

        case BuildingInformation::Type::Road:
            generateRoad(conf, area);
            break;

        case BuildingInformation::Type::Sanity:
            generateSanity(conf, area);
            break;

        case BuildingInformation::Type::School:
            generateSchool(conf, area);
            break;

        case BuildingInformation::Type::Storage:
            generateStorage(conf, area);
            break;

        default:
            qDebug() << "WARNING: Cannot create building of type " + conf.getTitle() + ". Skipping the creation.";
    }
}



void StaticElementHandler::createNatureElement(const NatureElementInformation& conf, const MapArea& area)
{
    QSharedPointer<NatureElement> element(new NatureElement(conf, area));
    currentState.natureElements.insert(element.get(), element);
    natureElementSearchEngine.registerRawMaterial(conf, area);

    registerNatureElementInDetailsCache(conf, area);
}



void StaticElementHandler::generateFarm(const BuildingInformation& conf, const MapArea& area)
{
    auto building(FarmBuilding::Create(characterFactory, conf, area, getBestBuildingEntryPoint(area)));
    currentState.buildings.insert(building.get(), building);

    processor.registerBuilding(building);
    populationHandler.registerWorkingPlace(building);
    registerBuildingInDetailsCache(area);
}



void StaticElementHandler::generateHouse(const BuildingInformation& conf, const MapArea& area)
{
    auto building(HouseBuilding::Create(*currentState.entryPoint.get(), populationHandler, conf, area, getBestBuildingEntryPoint(area)));
    currentState.buildings.insert(building.get(), building);

    processor.registerBuilding(building);
    registerBuildingInDetailsCache(area);
}



void StaticElementHandler::generateLaboratory(const BuildingInformation& conf, const MapArea& area)
{
    auto building(LaboratoryBuilding::Create(characterFactory, conf, area, getBestBuildingEntryPoint(area)));
    currentState.buildings.insert(building.get(), building);

    processor.registerBuilding(building);
    populationHandler.registerWorkingPlace(building);
    registerBuildingInDetailsCache(area);
    buildingSearchEngine.registerBuilding(building);
}



void StaticElementHandler::generateProducer(const BuildingInformation& conf, const MapArea& area)
{
    auto building(ProducerBuilding::Create(
        natureElementSearchEngine,
        characterFactory,
        conf,
        area,
        getBestBuildingEntryPoint(area)
    ));
    currentState.buildings.insert(building.get(), building);

    processor.registerBuilding(building);
    populationHandler.registerWorkingPlace(building);
    registerBuildingInDetailsCache(area);
}



void StaticElementHandler::generateSanity(const BuildingInformation& conf, const MapArea& area)
{
    auto building(SanityBuilding::Create(characterFactory, conf, area, getBestBuildingEntryPoint(area)));
    currentState.buildings.insert(building.get(), building);

    processor.registerBuilding(building);
    populationHandler.registerWorkingPlace(building);
    registerBuildingInDetailsCache(area);
}



void StaticElementHandler::generateSchool(const BuildingInformation& conf, const MapArea& area)
{
    auto building(SchoolBuilding::Create(
        buildingSearchEngine,
        characterFactory,
        conf,
        area,
        getBestBuildingEntryPoint(area)
    ));
    currentState.buildings.insert(building.get(), building);

    processor.registerBuilding(building);
    populationHandler.registerWorkingPlace(building);
    registerBuildingInDetailsCache(area);
}



void StaticElementHandler::generateStorage(const BuildingInformation& conf, const MapArea& area)
{
    auto building(StorageBuilding::Create(conf, area, getBestBuildingEntryPoint(area)));
    currentState.buildings.insert(building.get(), building);

    processor.registerBuilding(building);
    populationHandler.registerWorkingPlace(building);
    registerBuildingInDetailsCache(area);
    buildingSearchEngine.registerStorageBuilding(building);
}



void StaticElementHandler::generateRoad(const BuildingInformation& conf, const MapArea& area)
{
    QSharedPointer<AbstractBuilding> road(new Road(conf, area));
    currentState.buildings.insert(road.get(), road);

    registerRoadInDetailsCache(area);
}



MapCoordinates StaticElementHandler::getBestBuildingEntryPoint(const MapArea& area) const
{
    // Fetch a location around the area, starting at the coordinates at north of left point, and turning clockwise
    // around the area.

    auto left(area.getLeft());
    auto right(area.getRight());
    int moveX(1);
    int moveY(0);

    MapCoordinates coordinates(left.getNorth());
    while (!detailsCache.roadCoordinates.contains(coordinates.getHash())) {
        coordinates.setX(coordinates.getX() + moveX);
        coordinates.setY(coordinates.getY() + moveY);

        if (moveX == 1 && coordinates.getX() > right.getX()) {
            // Overstep top corner.
            moveX = 0;
            moveY = 1;
            coordinates.setY(coordinates.getY() + moveY);
        }
        else if (moveY == 1 && coordinates.getY() > right.getY()) {
            // Overstep right corner.
            moveX = -1;
            moveY = 0;
            coordinates.setX(coordinates.getX() + moveX);
        }
        else if (moveX == -1 && coordinates.getX() < left.getX()) {
            // Overstep bottom corner.
            moveX = 0;
            moveY = -1;
            coordinates.setY(coordinates.getY() + moveY);
        }
        else if (moveY == -1 && coordinates.getY() < left.getY()) {
            // Overstep left corner. No road nodefound.
            return MapCoordinates();
        }
    }

    return coordinates;
}



void StaticElementHandler::registerBuildingInDetailsCache(const MapArea& area)
{
    for (auto coordinates : area) {
        auto hash(coordinates.getHash());
        detailsCache.nonTraversableCoordinates << hash;
        detailsCache.nonConstructibleCoordinates << hash;
    }
}



void StaticElementHandler::registerRoadInDetailsCache(const MapArea& area)
{
    for (auto coordinates : area) {
        auto hash(coordinates.getHash());
        detailsCache.roadCoordinates << hash;
        detailsCache.nonConstructibleCoordinates << hash;
    }
}



void StaticElementHandler::registerNatureElementInDetailsCache(
    const NatureElementInformation& conf,
    const MapArea& area
) {
    for (auto coordinates : area) {
        auto hash(coordinates.getHash());
        detailsCache.nonConstructibleCoordinates.insert(hash);
        if (!conf.isTraversable()) {
            detailsCache.nonTraversableCoordinates.insert(hash);
        }
    }
}
