#include "Map.hpp"

#include <QDebug>

#include "engine/element/dynamic/RandomWalker.hpp"
#include "engine/element/static/AbstractProcessableStaticMapElement.hpp"
#include "engine/element/static/CityEntryPoint.hpp"
#include "engine/element/static/HousingBuilding.hpp"
#include "engine/element/static/MaintenanceBuilding.hpp"
#include "engine/element/static/Road.hpp"



Map::Map(const QSize& size, const QString& confFilePath, const MapCoordinates& cityEntryPointLocation) :
    QObject(),
    size(size),
    conf(confFilePath),
    cityStatus(10000),
    roadGraph(new RoadGraph(this)),
    processor(new TimeCycleProcessor(this)),
    elementList(),
    staticElementList(),
    entryPoint(new CityEntryPoint(this, cityEntryPointLocation))
{
    processor->registerProcessable(entryPoint);
    elementList.append(entryPoint);
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



void Map::createStaticElement(
    AbstractStaticMapElement::Type type,
    const MapArea& area
) {
    if (!isFreeArea(area)) {
        qDebug() << "ERROR: Try to create a static element on an occupyed area " + area.toString() + ". Skiping the creation.";
        return;
    }

    AbstractStaticMapElement* pointer;
    switch (type) {
        case AbstractStaticMapElement::Type::None:
            throw UnexpectedException("Try to create a static element of type None.");

        case AbstractStaticMapElement::Type::House: {
            auto element(new HousingBuilding(this, area, getAutoEntryPoint(area)));
            pointer = element;
            processor->registerProcessable(element);
            elementList.append(element);
            staticElementList.append(element);
            break;
        }

        case AbstractStaticMapElement::Type::Maintenance: {
            auto element(new MaintenanceBuilding(this, area, getAutoEntryPoint(area)));
            pointer = element;
            processor->registerProcessable(element);
            elementList.append(element);
            staticElementList.append(element);

            connect(element, &MaintenanceBuilding::requestDynamicElementCreation, [this, element](
                AbstractDynamicMapElement::Type type,
                const int randomWalkerCredit,
                const qreal speed,
                std::function<void(AbstractDynamicMapElement*)> afterCreation
            ) {
                createDynamicElement(type, element, randomWalkerCredit, speed, afterCreation);
            });
            connect(element, &MaintenanceBuilding::requestDynamicElementDestruction, this, &Map::destroyElement);
            break;
        }

        case AbstractStaticMapElement::Type::Road: {
            if (area.getSize().getValue() > 1) {
                throw UnexpectedException("Try to create a road on an area bigger than 1: " + area.toString());
            }
            auto coordinates(area.getLeft());
            auto element(new Road(coordinates));
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
    AbstractDynamicMapElement::Type type,
    AbstractProcessableStaticMapElement* issuer,
    const int randomWalkerCredit,
    const qreal speed,
    std::function<void(AbstractDynamicMapElement*)> afterCreation
) {
    AbstractDynamicMapElement* pointer;
    switch (type) {
        case AbstractDynamicMapElement::Type::None:
            throw UnexpectedException("Try to create a dynamic element of type None.");

        case AbstractDynamicMapElement::Type::RandomWalker: {
            auto element(new RandomWalker(this, roadGraph, issuer, randomWalkerCredit, speed));
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



AbstractStaticMapElement* Map::fetchStaticElement(const AbstractStaticMapElement* element) const
{
    for (auto elementFromList : staticElementList) {
        if (elementFromList == element) {
            return elementFromList;
        }
    }

    return nullptr;
}
