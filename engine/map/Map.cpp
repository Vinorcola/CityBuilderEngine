#include "Map.hpp"

#include <QDebug>
#include <QSharedPointer>

#include "engine/element/dynamic/RandomWalker.hpp"
#include "engine/element/static/AbstractStaticMapElement.hpp"
#include "engine/element/static/HousingBuilding.hpp"
#include "engine/element/static/MaintenanceBuilding.hpp"
#include "engine/element/static/Road.hpp"



Map::Map(const QSize& size, const QString& confFilePath, const MapCoordinates& cityEntryPointLocation) :
    QObject(),
    size(size),
    conf(confFilePath),
    cityStatus(10000),
    roadGraph(),
    processor(this),
    staticElementList(),
    dynamicElementList(),
    entryPoint(new CityEntryPoint(cityEntryPointLocation))
{
    processor.registerProcessable(qWeakPointerCast<AbstractProcessable, CityEntryPoint>(entryPoint));
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

    QSharedPointer<AbstractStaticMapElement> element;
    const RoadGraphNode* entryPointNode;
    switch (type) {
        case StaticElementType::None:
            throw UnexpectedException("Try to create a static element of type None.");

        case StaticElementType::House:{
            entryPointNode = roadGraph.fetchNodeArround(area);
            QSharedPointer<HousingBuilding> tmp(new HousingBuilding(*this, area, entryPointNode ? entryPointNode->getCoordinates() : MapCoordinates(), cityStatus, entryPoint.toWeakRef()));
            element = qSharedPointerCast<AbstractStaticMapElement, HousingBuilding>(tmp);
            processor.registerProcessable(
                qWeakPointerCast<AbstractProcessable, HousingBuilding>(tmp)
            );
            break;
        }

        case StaticElementType::Maintenance: {
            entryPointNode = roadGraph.fetchNodeArround(area);
            QSharedPointer<MaintenanceBuilding> tmp(new MaintenanceBuilding(*this, area, entryPointNode ? entryPointNode->getCoordinates() : MapCoordinates()));
            element = qSharedPointerCast<AbstractStaticMapElement, MaintenanceBuilding>(tmp);
            processor.registerProcessable(
                qWeakPointerCast<AbstractProcessable, MaintenanceBuilding>(tmp)
            );
            break;
        }

        case StaticElementType::Road: {
            if (area.getSize().getValue() > 1) {
                throw UnexpectedException("Try to create a road on an area bigger than 1: " + area.toString());
            }
            auto coordinates(area.getLeft());
            element.reset(new Road(coordinates));
            roadGraph.createNode(coordinates);
            break;
        }
    }

    staticElementList.append(element);

    emit staticElementCreated(element.toWeakRef());
}



QWeakPointer<AbstractDynamicMapElement> Map::createDynamicElement(Map::DynamicElementType type,
    const AbstractProcessableStaticMapElement* issuer,
    const int randomWalkerCredit,
    const qreal speed
) {
    QSharedPointer<AbstractDynamicMapElement> element;
    switch (type) {
        case DynamicElementType::None:
            throw UnexpectedException("Try to create a dynamic element of type None.");

        case DynamicElementType::RandomWalker: {
            auto issuerAccess(qSharedPointerCast<AbstractProcessableStaticMapElement, AbstractStaticMapElement>(fetchStaticElement(issuer)));
            element.reset(new RandomWalker(roadGraph, issuerAccess.toWeakRef(), randomWalkerCredit, speed));
            break;
        }

        default:
            throw UnexpectedException("Try to create a dynamic element of unknown type.");
    }

    processor.registerProcessable(element.toWeakRef());
    dynamicElementList.append(element);

    emit dynamicElementCreated(element.toWeakRef());

    return element.toWeakRef();
}



void Map::destroyDynamicElement(AbstractDynamicMapElement* element)
{
    for (auto elementAccess: dynamicElementList) {
        if (elementAccess == element) {
            // No need to unregister the processable inthe TimeCycleProcessor: it will automatically be unregistered.
            dynamicElementList.removeOne(elementAccess);
            return;
        }
    }
}



QSharedPointer<AbstractStaticMapElement> Map::fetchStaticElement(const AbstractStaticMapElement* element) const
{
    for (auto elementFromList : staticElementList) {
        if (elementFromList == element) {
            return elementFromList;
        }
    }

    return nullptr;
}
