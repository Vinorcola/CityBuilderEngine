#include "Map.hpp"

#include <QDebug>
#include <yaml-cpp/yaml.h>

#include "src/engine/element/dynamic/Character.hpp"
#include "src/engine/element/static/behavior/BehaviorFactory.hpp"
#include "src/engine/element/static/CityEntryPoint.hpp"
#include "src/engine/element/static/NatureElement.hpp"
#include "src/engine/element/static/ProcessableBuilding.hpp"
#include "src/engine/element/static/Road.hpp"
#include "src/engine/map/roadGraph/RoadGraph.hpp"
#include "src/engine/map/roadGraph/RoadGraphNode.hpp"
#include "src/engine/map/searchEngine/SearchEngine.hpp"
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
    roadGraph(new RoadGraph(this)),
    processor(new TimeCycleProcessor(this, loader.getDate())),
    searchEngine(new SearchEngine(this, buildingList)),
    behaviorFactory(new BehaviorFactory(this, this, searchEngine)),
    characterList(),
    buildingList(),
    natureElementList(),
    traversableLocationCache(),
    roadLocationCache(),
    entryPoint(),
    pathGenerator(*this)
{
    // Load buildings.
    for (auto buildingInfo : loader.getBuildings()) {
        auto buildingConf(conf->getBuildingConf(buildingInfo["type"].as<QString>()));
        createBuilding(
            buildingConf,
            MapArea(
                MapCoordinates(buildingInfo["position"]["x"].as<int>(), buildingInfo["position"]["y"].as<int>()),
                buildingConf->getSize()
            )
        );
    }

    // Load nature elements.
    for (auto natureElementInfo : loader.getNatureElements()) {
        auto natureElementConf(conf->getNatureElementConf(natureElementInfo["type"].as<QString>()));
        createNatureElement(
            natureElementConf,
            MapArea(
                MapCoordinates(natureElementInfo["position"]["x"].as<int>(), natureElementInfo["position"]["y"].as<int>()),
                MapSize(1) // For now, only single tiles nature elements are supported.
            )
        );
    }

    connect(cityStatus, &CityStatus::populationChanged, this, &Map::populationChanged);
    connect(processor, &TimeCycleProcessor::dateChanged, this, &Map::dateChanged);
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



bool Map::isFreeCoordinates(const MapCoordinates& coordinates) const
{
    for (auto element : buildingList) {
        if (element->getArea().isInside(coordinates)) {
            return false;
        }
    }

    return true;
}



bool Map::isFreeArea(const MapArea& area) const
{
    if (!isValidArea(area)) {
        return false;
    }

    auto left(area.getLeft());
    auto right(area.getRight());

    MapCoordinates coordinates(left);
    while (coordinates.getY() <= right.getY()) {
        while (coordinates.getX() <= right.getX()) {
            if (!isFreeCoordinates(coordinates)) {
                return false;
            }
            coordinates = coordinates.getEast();
        }
        coordinates = MapCoordinates(left.getX(), coordinates.getY() + 1);
    }

    return true;
}



const RoadGraphNode* Map::resolveRoad(const MapCoordinates& coordinates) const
{
    return roadGraph->fetchNodeAt(coordinates);
}



QList<const RoadGraphNode*> Map::getShortestRoadPathBetween(
    const MapCoordinates& origin,
    const MapCoordinates& destination
) const {

    return roadGraph->getShortestPathBetween(origin, destination);
}



MapCoordinates Map::getAutoEntryPoint(const MapArea& area) const
{
    auto node(roadGraph->fetchNodeArround(area));
    if (node) {
        return node->getCoordinates();
    }

    return MapCoordinates();
}



const TimeCycleProcessor* Map::getProcessor() const
{
    return processor;
}



const QLinkedList<Building*>& Map::getBuildings() const
{
    return buildingList;
}



const QLinkedList<Character*>& Map::getCharacters() const
{
    return characterList;
}



const QLinkedList<NatureElement*>& Map::getNatureElements() const
{
    return natureElementList;
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
    return isValidCoordinates(location) && traversableLocationCache.isLocationTraversable(location);
}



bool Map::hasRoadAtLocation(const MapCoordinates& location) const
{
    return isValidCoordinates(location) && roadLocationCache.hasRoadAtLocation(location);
}



void Map::pause(const bool pause)
{
    processor->pause(pause);
}



void Map::setProcessorSpeedRatio(const qreal speedRatio)
{
    processor->setSpeedRatio(speedRatio);
}



void Map::createBuilding(const BuildingInformation* conf, const MapArea& area)
{
    if (!isValidArea(area)) {
        throw UnexpectedException("Try to create a building on an invalid area: " + area.toString() + ".");
    }
    if (area.getSize() != conf->getSize()) {
        throw UnexpectedException("Try to build a building on a area not matching the configured size.");
    }
    if (!isFreeArea(area)) {
        qDebug() << "WARNING: Try to create a building on an occupyed area " + area.toString() + ". Skiping the creation.";
        return;
    }

    Building* pointer;
    switch (conf->getType()) {
        case BuildingInformation::Type::None:
            throw UnexpectedException("Try to create a static element of type None.");

        case BuildingInformation::Type::Building: {
            auto element(new ProcessableBuilding(this, behaviorFactory, conf, area, getAutoEntryPoint(area)));
            pointer = element;
            processor->registerBuilding(element);
            buildingList.append(element);
            traversableLocationCache.registerNonTraversableArea(area);

            connect(element, &ProcessableBuilding::requestCharacterCreation, [this, element](
                const CharacterInformation* elementConf,
                std::function<void(Character*)> afterCreation
            ) {
                createCharacter(elementConf, element, afterCreation);
            });
            connect(element, &ProcessableBuilding::requestCharacterDestruction, this, &Map::destroyCharacter);
            break;
        }

        case BuildingInformation::Type::CityEntryPoint: {
            auto coordinates(area.getLeft());
            entryPoint = new CityEntryPoint(this, behaviorFactory, conf, coordinates);
            pointer = entryPoint;
            roadGraph->createNode(coordinates);
            processor->registerBuilding(entryPoint);
            buildingList.append(entryPoint);
            roadLocationCache.registerRoadLocation(area.getLeft());

            connect(entryPoint, &CityEntryPoint::requestCharacterCreation, [this](
                const CharacterInformation* elementConf,
                std::function<void(Character*)> afterCreation
            ) {
                createCharacter(elementConf, entryPoint, afterCreation);
            });
            break;
        }

        case BuildingInformation::Type::Road: {
            auto coordinates(area.getLeft());
            auto element(new Road(this, conf, coordinates));
            pointer = element;
            roadGraph->createNode(coordinates);
            buildingList.append(element);
            roadLocationCache.registerRoadLocation(area.getLeft());
            break;
        }

        default:
            throw UnexpectedException("Try to create a static element of unknown type.");
    }

    emit buildingCreated(pointer);
}



void Map::createCharacter(
    const CharacterInformation* conf,
    ProcessableBuilding* issuer,
    std::function<void(Character*)> afterCreation
) {
    auto character(new Character(this, pathGenerator, conf, issuer, conf->getWanderingCredits()));
    processor->registerCharacter(character);
    characterList.append(character);
    afterCreation(character);

    emit characterCreated(character);
}



void Map::createNatureElement(const NatureElementInformation* conf, const MapArea& area)
{
    if (!isValidArea(area)) {
        throw UnexpectedException("Try to create a nature element on an invalid area: " + area.toString() + ".");
    }
    if (!isFreeArea(area)) {
        qDebug() << "WARNING: Try to create a building on an occupyed area " + area.toString() + ". Skiping the creation.";
        return;
    }

    auto natureElement(new NatureElement(this, conf, area));
    natureElementList.append(natureElement);
    if (!conf->isTraversable()) {
        traversableLocationCache.registerNonTraversableArea(area);
    }

    emit natureElementCreated(natureElement);
}



void Map::destroyBuilding(Building* building, std::function<void()> afterDestruction)
{
    for (auto fromList : buildingList) {
        if (fromList == building) {
            buildingList.removeOne(building);
            auto roadBuilding(dynamic_cast<Road*>(building));
            if (roadBuilding) {
                roadLocationCache.unregisterRoadLocation(building->getArea().getLeft());
            }
            delete building;
            afterDestruction();
            return;
        }
    }
}



void Map::destroyCharacter(Character* character, std::function<void()> afterDestruction)
{
    for (auto fromList : characterList) {
        if (fromList == character) {
            characterList.removeOne(character);
            delete character;
            afterDestruction();
            return;
        }
    }
}



void Map::changePopulation(const int populationDelta)
{
    cityStatus->updatePopulation(populationDelta);
}



void Map::freeHousingCapacityChanged(
    const int previousHousingCapacity,
    const int newHousingCapacity,
    std::function<void(Character*)> onImmigrantCreation
) {
    cityStatus->updateFreeHousingPlaces(newHousingCapacity - previousHousingCapacity);
    if (newHousingCapacity > 0) {
        entryPoint->requestImmigrant(onImmigrantCreation);
    }
}



Building* Map::fetchBuilding(const Building* building) const
{
    for (auto fromList : buildingList) {
        if (fromList == building) {
            return fromList;
        }
    }

    return nullptr;
}
