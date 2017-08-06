#include "Map.hpp"

#include <QDebug>
#include <yaml-cpp/yaml.h>

#include "engine/element/dynamic/RandomWalker.hpp"
#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"
#include "engine/element/static/CityEntryPoint.hpp"
#include "engine/element/static/CultureBuilding.hpp"
#include "engine/element/static/HousingBuilding.hpp"
#include "engine/element/static/Road.hpp"



Map::Map(const Conf* conf, const MapLoader& loader) :
    QObject(),
    conf(conf),
    size(loader.getSize()),
    cityStatus(new CityStatus(this, loader.getBudget())),
    roadGraph(new RoadGraph(this)),
    processor(new TimeCycleProcessor(this)),
    elementList(),
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
    qDeleteAll(elementList);
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
        sum >= 0 && sum < size.width()
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



const QLinkedList<AbstractMapElement*>& Map::getElements() const
{
    return elementList;
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

        case StaticElementInformation::Type::CityEntryPoint: {
            auto coordinates(area.getLeft());
            entryPoint = new CityEntryPoint(this, elementConf, coordinates, conf->getDynamicElementConf("immigrant"));
            pointer = entryPoint;
            roadGraph->createNode(coordinates);
            processor->registerProcessable(entryPoint);
            elementList.append(entryPoint);
            staticElementList.append(entryPoint);

            connect(entryPoint, &CityEntryPoint::requestDynamicElementCreation, [this](
                const DynamicElementInformation* elementConf,
                std::function<void(AbstractDynamicMapElement*)> afterCreation
            ) {
                createDynamicElement(elementConf, entryPoint, afterCreation);
            });
            break;
        }

        case StaticElementInformation::Type::CultureBuilding: {
            auto element(new CultureBuilding(this, elementConf, area, getAutoEntryPoint(area)));
            pointer = element;
            processor->registerProcessable(element);
            elementList.append(element);
            staticElementList.append(element);

            connect(element, &ServiceBuilding::requestDynamicElementCreation, [this, element](
                    const DynamicElementInformation* elementConf,
                std::function<void(AbstractDynamicMapElement*)> afterCreation
            ) {
                createDynamicElement(elementConf, element, afterCreation);
            });
            connect(element, &ServiceBuilding::requestDynamicElementDestruction, this, &Map::destroyElement);
            break;
        }

        case StaticElementInformation::Type::HousingBuilding: {
            auto element(new HousingBuilding(this, elementConf, area, getAutoEntryPoint(area)));
            pointer = element;
            processor->registerProcessable(element);
            elementList.append(element);
            staticElementList.append(element);

            connect(element, &ServiceBuilding::requestDynamicElementCreation, [this, element](
                    const DynamicElementInformation* elementConf,
                std::function<void(AbstractDynamicMapElement*)> afterCreation
            ) {
                createDynamicElement(elementConf, element, afterCreation);
            });
            connect(element, &ServiceBuilding::requestDynamicElementDestruction, this, &Map::destroyElement);
            connect(element, &HousingBuilding::freeCapacityChanged, this, &Map::freeHousingCapacityChanged);
            connect(element, &HousingBuilding::inhabitantsChanged, this, &Map::populationChanged);
            break;
        }

        case StaticElementInformation::Type::ServiceBuilding: {
            auto element(new ServiceBuilding(this, elementConf, area, getAutoEntryPoint(area)));
            pointer = element;
            processor->registerProcessable(element);
            elementList.append(element);
            staticElementList.append(element);

            connect(element, &ServiceBuilding::requestDynamicElementCreation, [this, element](
                    const DynamicElementInformation* elementConf,
                std::function<void(AbstractDynamicMapElement*)> afterCreation
            ) {
                createDynamicElement(elementConf, element, afterCreation);
            });
            connect(element, &ServiceBuilding::requestDynamicElementDestruction, this, &Map::destroyElement);
            break;
        }

        case StaticElementInformation::Type::Road: {
            auto coordinates(area.getLeft());
            auto element(new Road(elementConf, coordinates));
            pointer = element;
            roadGraph->createNode(coordinates);
            elementList.append(element);
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
    std::function<void(AbstractDynamicMapElement*)> afterCreation
) {
    AbstractDynamicMapElement* pointer;
    switch (elementConf->getType()) {
        case DynamicElementInformation::Type::None:
            throw UnexpectedException("Try to create a dynamic element of type None.");

        case DynamicElementInformation::Type::RandomWalker: {
            auto element(new RandomWalker(this, elementConf, roadGraph, issuer));
            pointer = element;
            processor->registerProcessable(element);
            elementList.append(element);
            afterCreation(element);
            break;
        }

        case DynamicElementInformation::Type::TargetedWalker: {
            auto element(new TargetedWalker(this, elementConf, roadGraph, issuer));
            pointer = element;
            processor->registerProcessable(element);
            elementList.append(element);
            afterCreation(element);
            break;
        }

        default:
            throw UnexpectedException("Try to create a dynamic element of unknown type.");
    }

    emit dynamicElementCreated(pointer);
}



void Map::destroyElement(AbstractDynamicMapElement* element, std::function<void()> afterDestruction)
{
    for (auto elementFromList: elementList) {
        if (elementFromList== element) {
            // No need to unregister the processable in the TimeCycleProcessor: it will automatically be unregistered.
            elementList.removeOne(elementFromList);
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
    std::function<void(TargetedWalker*)> onImmigrantCreation
) {
    cityStatus->updateFreeHousingPlaces(newHousingCapacity - previousHousingCapacity);
    if (newHousingCapacity > 0) {
        entryPoint->registerImmigrantRequest(static_cast<AbstractProcessableStaticMapElement*>(sender()), onImmigrantCreation);
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
