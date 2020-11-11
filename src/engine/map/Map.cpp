#include "Map.hpp"

#include <QDebug>
#include <yaml-cpp/yaml.h>

#include "src/engine/element/dynamic/Character.hpp"
#include "src/engine/element/static/building/HouseBuilding.hpp"
#include "src/engine/element/static/NatureElement.hpp"
#include "src/engine/element/static/ProcessableBuilding.hpp"
#include "src/engine/map/CityStatus.hpp"
#include "src/engine/map/MapArea.hpp"
#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/map/MapLoader.hpp"
#include "src/engine/processing/TimeCycleProcessor.hpp"
#include "src/exceptions/UnexpectedException.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/CharacterInformation.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/global/conf/NatureElementInformation.hpp"
#include "src/global/yamlLibraryEnhancement.hpp"



Map::Map(const Conf* conf, const MapLoader& loader) :
    QObject(),
    conf(conf),
    size(loader.getSize()),
    cityStatus(new CityStatus(this, loader.getBudget())),
    processor(new TimeCycleProcessor(this, loader.getDate())),
    mapDetailsCache(),
    pathGenerator(*this),
    searchEngine(pathGenerator),
    elementHandler(*this, searchEngine, pathGenerator),
    entryPoint(this, elementHandler, conf->getBuildingConf("mapEntryPoint"), loader.getEntryPoint(), conf->getCharacterConf("immigrant"))
{
    connect(&elementHandler, &ElementHandler::buildingCreated, [this](QSharedPointer<Building> building) {
        auto processableBuilding(building.dynamicCast<ProcessableBuilding>());
        if (processableBuilding) {
            processor->registerBuilding(*processableBuilding);

            auto houseBuilding(processableBuilding.dynamicCast<HouseBuilding>());
            if (houseBuilding) {
                connect(houseBuilding.get(), &HouseBuilding::populationChanged, this, &Map::changePopulation);
            }
        }

        mapDetailsCache.registerBuildingConstruction(building->getConf(), building->getArea());

        emit buildingCreated(building);
    });
    connect(&elementHandler, &ElementHandler::characterCreated, [this](QSharedPointer<Character> character) {
        processor->registerCharacter(character.get());

        emit characterCreated(character);
    });
    connect(&elementHandler, &ElementHandler::natureElementCreated, [this](NatureElement& natureElement) {
        mapDetailsCache.registerNatureElement(natureElement.getConf(), natureElement.getArea());
        searchEngine.registerRawMaterial(natureElement.getConf(), natureElement.getArea());

        emit natureElementCreated(natureElement);
    });

    connect(cityStatus, &CityStatus::populationChanged, this, &Map::populationChanged);
    connect(processor, &TimeCycleProcessor::dateChanged, this, &Map::dateChanged);

    // Register map entry point.
    processor->registerBuilding(entryPoint);

    // Load buildings.
    for (auto buildingInfo : loader.getBuildings()) {
        auto& buildingConf(conf->getBuildingConf(buildingInfo["type"].as<QString>()));
        createBuilding(
            buildingConf,
            MapArea(
                buildingInfo["position"].as<MapCoordinates>(),
                buildingConf.getSize()
            )
        );
    }

    // Load nature elements.
    for (auto natureElementInfo : loader.getNatureElements()) {
        auto& natureElementConf(conf->getNatureElementConf(natureElementInfo["type"].as<QString>()));
        elementHandler.generateNatureElement(
            natureElementConf,
            MapArea(
                natureElementInfo["position"].as<MapCoordinates>(),
                MapSize(1) // For now, only single tile nature elements are supported.
            )
        );
    }
}



const QSize& Map::getSize() const
{
    return size;
}




bool Map::isValidCoordinates(const MapCoordinates& coordinates) const
{
    int sum(coordinates.getY() + coordinates.getX());
    int diff(coordinates.getY() - coordinates.getX());
    return (
        diff >= 0 && diff < size.height() &&
        sum >= 0 && sum <= size.width()
    );
}



bool Map::isValidArea(const MapArea& area) const
{
    return (
        isValidCoordinates(area.getLeft()) &&
        isValidCoordinates(area.getRight()) &&
        isValidCoordinates(area.getTop()) &&
        isValidCoordinates(area.getBottom())
    );
}



bool Map::isConstructible(const MapCoordinates& coordinates) const
{
    return mapDetailsCache.isLocationConstructible(coordinates);
}



bool Map::isConstructible(const MapArea& area) const
{
    if (!isValidArea(area)) {
        return false;
    }

    auto left(area.getLeft());
    auto right(area.getRight());

    MapCoordinates coordinates(left);
    while (coordinates.getY() <= right.getY()) {
        while (coordinates.getX() <= right.getX()) {
            if (!isConstructible(coordinates)) {
                return false;
            }
            coordinates = coordinates.getEast();
        }
        coordinates = MapCoordinates(left.getX(), coordinates.getY() + 1);
    }

    return true;
}



MapCoordinates Map::getBestEntryPoint(const MapArea& area) const
{
    return mapDetailsCache.getBestEntryPointForArea(area);
}



const TimeCycleProcessor* Map::getProcessor() const
{
    return processor;
}



const std::list<QSharedPointer<Building>>& Map::getBuildings() const
{
    return elementHandler.getBuildings();
}



const std::list<QSharedPointer<Character>>& Map::getCharacters() const
{
    return elementHandler.getCharacters();
}



const std::list<NatureElement*>& Map::getNatureElements() const
{
    return elementHandler.getNatureElements();
}



ImmigrantGeneratorInterface& Map::getImmigrantGenerator()
{
    return entryPoint;
}



int Map::getCurrentBudget() const
{
    return cityStatus->getBudget();
}



int Map::getCurrentPopulation() const
{
    return cityStatus->getPopulation();
}



const CycleDate& Map::getCurrentDate() const
{
    return processor->getCurrentDate();
}



bool Map::isLocationTraversable(const MapCoordinates& location) const
{
    return isValidCoordinates(location) && mapDetailsCache.isLocationTraversable(location);
}



bool Map::hasRoadAtLocation(const MapCoordinates& location) const
{
    return isValidCoordinates(location) && mapDetailsCache.hasRoadAtLocation(location);
}



bool Map::canConstructRoadAtLocation(const MapCoordinates& location) const
{
    return isValidCoordinates(location) && (
        mapDetailsCache.isLocationConstructible(location) || mapDetailsCache.hasRoadAtLocation(location)
    );
}



QList<MapCoordinates> Map::getShortestPathForRoad(
    const MapCoordinates& origin,
    const MapCoordinates& target
) const {

    return pathGenerator.generateShortestPathForRoad(origin, target);
}



void Map::pause(const bool pause)
{
    processor->pause(pause);
}



void Map::setProcessorSpeedRatio(const qreal speedRatio)
{
    processor->setSpeedRatio(speedRatio);
}



void Map::createBuilding(const BuildingInformation& conf, const MapArea& area)
{
    if (!isConstructible(area)) {
        qDebug() << "WARNING: Try to create a building on an occupyed area " + area.toString() + ". Skiping the creation.";
        return;
    }

    switch (conf.getType()) {
        case BuildingInformation::Type::Farm:
            elementHandler.generateFarm(conf, area);
            break;

        case BuildingInformation::Type::House:
            elementHandler.generateHouse(conf, area);
            break;

        case BuildingInformation::Type::Laboratory:
            elementHandler.generateLaboratory(conf, area);
            break;

        case BuildingInformation::Type::Producer:
            elementHandler.generateProducer(conf, area);
            break;

        case BuildingInformation::Type::Road:
            elementHandler.generateRoad(conf, area.getLeft());
            break;

        case BuildingInformation::Type::Sanity:
            elementHandler.generateSanity(conf, area);
            break;

        case BuildingInformation::Type::School:
            elementHandler.generateSchool(conf, area);
            break;

        case BuildingInformation::Type::Storage:
            elementHandler.generateStorage(conf, area);
            break;
    }
}



void Map::changePopulation(const int populationDelta)
{
    cityStatus->updatePopulation(populationDelta);
}
