#include "Map.hpp"

#include <QDebug>
#include <yaml-cpp/yaml.h>

#include "engine/element/dynamic/Character.hpp"
#include "engine/element/static/behavior/BehaviorFactory.hpp"
#include "engine/element/static/Building.hpp"
#include "engine/element/static/CityEntryPoint.hpp"
#include "engine/element/static/Road.hpp"
#include "engine/map/roadGraph/RoadGraph.hpp"
#include "engine/map/roadGraph/RoadGraphNode.hpp"
#include "engine/map/searchEngine/SearchEngine.hpp"
#include "engine/map/CityStatus.hpp"
#include "engine/map/MapArea.hpp"
#include "engine/map/MapCoordinates.hpp"
#include "engine/map/MapLoader.hpp"
#include "engine/processing/TimeCycleProcessor.hpp"
#include "exceptions/UnexpectedException.hpp"
#include "global/conf/Conf.hpp"
#include "global/conf/DynamicElementInformation.hpp"
#include "global/conf/StaticElementInformation.hpp"



Map::Map(const Conf* conf, const MapLoader& loader) :
    QObject(),
    conf(conf),
    size(loader.getSize()),
    cityStatus(new CityStatus(this, loader.getBudget())),
    roadGraph(new RoadGraph(this)),
    processor(new TimeCycleProcessor(this)),
    searchEngine(new SearchEngine(this, staticElementList)),
    behaviorFactory(new BehaviorFactory(this, this, searchEngine)),
    dynamicElementList(),
    staticElementList(),
    entryPoint()
{
    // Load static elements.
    for (auto elementInfo : loader.getStaticElements()) {
        auto elementConf(conf->getStaticElementConf(QString::fromStdString(elementInfo["type"].as<std::string>())));
        createStaticElement(
            elementConf,
            MapArea(
                MapCoordinates(elementInfo["position"]["x"].as<int>(), elementInfo["position"]["y"].as<int>()),
                elementConf->getSize()
            )
        );
    }
}



Map::~Map()
{
    qDeleteAll(dynamicElementList);
    qDeleteAll(staticElementList);
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
    for (auto element : staticElementList) {
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



const QLinkedList<Character*>& Map::getDynamicElements() const
{
    return dynamicElementList;
}



const QLinkedList<AbstractStaticMapElement*>& Map::getStaticElements() const
{
    return staticElementList;
}



void Map::pause(const bool pause)
{
    processor->pause(pause);
}



void Map::setProcessorSpeedRatio(const qreal speedRatio)
{
    processor->setSpeedRatio(speedRatio);
}



void Map::createStaticElement(
    const StaticElementInformation* elementConf,
    const MapArea& area
) {
    if (area.getSize() != elementConf->getSize()) {
        throw UnexpectedException("Try to build a static element on a area not matching the element size.");
    }
    if (!isFreeArea(area)) {
        qDebug() << "ERROR: Try to create a static element on an occupyed area " + area.toString() + ". Skiping the creation.";
        return;
    }

    AbstractStaticMapElement* pointer;
    switch (elementConf->getType()) {
        case StaticElementInformation::Type::None:
            throw UnexpectedException("Try to create a static element of type None.");

        case StaticElementInformation::Type::Building: {
            auto element(new Building(this, behaviorFactory, elementConf, area, getAutoEntryPoint(area)));
            pointer = element;
            processor->registerBuilding(element);
            staticElementList.append(element);

            connect(element, &Building::requestDynamicElementCreation, [this, element](
                const DynamicElementInformation* elementConf,
                std::function<void(Character*)> afterCreation
            ) {
                createDynamicElement(elementConf, element, afterCreation);
            });
            connect(element, &Building::requestDynamicElementDestruction, this, &Map::destroyCharacter);
            break;
        }

        case StaticElementInformation::Type::CityEntryPoint: {
            auto coordinates(area.getLeft());
            entryPoint = new CityEntryPoint(this, behaviorFactory, elementConf, coordinates);
            pointer = entryPoint;
            roadGraph->createNode(coordinates);
            processor->registerBuilding(entryPoint);
            staticElementList.append(entryPoint);

            connect(entryPoint, &CityEntryPoint::requestDynamicElementCreation, [this](
                const DynamicElementInformation* elementConf,
                std::function<void(Character*)> afterCreation
            ) {
                createDynamicElement(elementConf, entryPoint, afterCreation);
            });
            break;
        }

        case StaticElementInformation::Type::Road: {
            auto coordinates(area.getLeft());
            auto element(new Road(elementConf, coordinates));
            pointer = element;
            roadGraph->createNode(coordinates);
            staticElementList.append(element);
            break;
        }

        default:
            throw UnexpectedException("Try to create a static element of unknown type.");
    }

    emit staticElementCreated(pointer);
}



void Map::createDynamicElement(
    const DynamicElementInformation* elementConf,
    AbstractProcessableStaticMapElement* issuer,
    std::function<void(Character*)> afterCreation
) {
    Character* element;
    switch (elementConf->getType()) {
        case DynamicElementInformation::Type::None:
            throw UnexpectedException("Try to create a dynamic element of type None.");

        case DynamicElementInformation::Type::RandomWalker: {
            element = new Character(this, this, elementConf, issuer, elementConf->getWalkingCredit());
            processor->registerCharacter(element);
            dynamicElementList.append(element);
            afterCreation(element);
            break;
        }

        case DynamicElementInformation::Type::TargetedWalker: {
            element = new Character(this, this, elementConf, issuer);
            processor->registerCharacter(element);
            dynamicElementList.append(element);
            afterCreation(element);
            break;
        }

        default:
            throw UnexpectedException("Try to create a dynamic element of unknown type.");
    }

    emit dynamicElementCreated(element);
}



void Map::destroyCharacter(Character* character, std::function<void()> afterDestruction)
{
    for (auto elementFromList: dynamicElementList) {
        if (character == elementFromList) {
            dynamicElementList.removeOne(character);
            delete character;
            afterDestruction();
            return;
        }
    }
}



void Map::destroyStaticElement(AbstractStaticMapElement* element, std::function<void()> afterDestruction)
{
    for (auto elementFromList: staticElementList) {
        if (elementFromList== element) {
            staticElementList.removeOne(elementFromList);
            delete elementFromList;
            afterDestruction();
            return;
        }
    }
}



void Map::populationChanged(const int populationDelta)
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



AbstractStaticMapElement* Map::fetchStaticElement(const AbstractStaticMapElement* element) const
{
    for (auto elementFromList : staticElementList) {
        if (elementFromList == element) {
            return elementFromList;
        }
    }

    return nullptr;
}
