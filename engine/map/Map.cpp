#include "Map.hpp"

#include <QDebug>
#include <QSharedPointer>

#include "engine/element/building/MaintenanceBuilding.hpp"
#include "engine/element/building/Road.hpp"
#include "engine/element/character/RandomWalker.hpp"
#include "engine/element/AbstractStaticMapElement.hpp"



Map::Map(const QSize& size, const QString& confFilePath) :
    QObject(),
    size(size),
    conf(confFilePath),
    roadGraph(),
    processor(this),
    staticElementList(),
    dynamicElementList()
{

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



const TimeCycleProcessor& Map::getProcessor() const
{
    return processor;
}



void Map::createStaticElement(StaticElementType type, const MapArea& area)
{
    if (!isFreeArea(area)) {
        qDebug() << "ERROR: Try to create a static element on an occupyed area " + area.toString() + ". Skiping the creation.";
        return;
    }

    AbstractStaticMapElement* element;
    const RoadGraphNode* entryPointNode;
    switch (type) {
        case StaticElementType::None:
            throw UnexpectedException("Try to create a static element of type None.");

        case StaticElementType::Maintenance:
            entryPointNode = roadGraph.fetchNodeArround(area);
            element = new MaintenanceBuilding(*this, area, entryPointNode ? entryPointNode->getCoordinates() : MapCoordinates());
            processor.registerProcessable(static_cast<AbstractProcessableBuilding*>(element));
            break;

        case StaticElementType::Road:
            if (area.getSize().getValue() > 1) {
                throw UnexpectedException("Try to create a road on an area bigger than 1: " + area.toString());
            }
            element = new Road(roadGraph.createNode(area.getLeft()));
            break;
    }

    QSharedPointer<AbstractStaticMapElement> elementAccess(element);
    staticElementList.append(elementAccess);

    emit staticElementCreated(elementAccess.toWeakRef());
}



AbstractDynamicMapElement* Map::createDynamicElement(Map::DynamicElementType type, const MapCoordinates& initialLocation, const int randomWalkerCredit, const qreal speed)
{
    AbstractDynamicMapElement* element;
    switch (type) {
        case DynamicElementType::None:
            throw UnexpectedException("Try to create a dynamic element of type None.");

        case DynamicElementType::RandomWalker:
            element = new RandomWalker(roadGraph, initialLocation, randomWalkerCredit, speed);
            break;

        default:
            throw UnexpectedException("Try to create a dynamic element of unknown type.");
    }

    processor.registerProcessable(element);
    QSharedPointer<AbstractDynamicMapElement> elementAccess(element);
    dynamicElementList.append(elementAccess);

    emit dynamicElementCreated(elementAccess.toWeakRef());

    return element;
}



void Map::destroyDynamicElement(AbstractDynamicMapElement* element)
{
    for (auto elementAccess: dynamicElementList) {
        if (elementAccess.data() == element) {
            processor.unregisterProcessable(element);
            dynamicElementList.removeOne(elementAccess);
            elementAccess.clear();
            return;
        }
    }
}
