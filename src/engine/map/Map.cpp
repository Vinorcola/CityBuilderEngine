#include "Map.hpp"

#include <QtCore/QDebug>

#include "src/engine/loader/CityLoader.hpp"
#include "src/engine/map/MapArea.hpp"
#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/processing/CycleDate.hpp"
#include "src/global/conf/BuildingInformation.hpp"
#include "src/global/conf/Conf.hpp"
#include "src/global/conf/NatureElementInformation.hpp"



Map::Map(
    const Conf& conf,
    CityLoader& loader,
    PopulationRegistryInterface& populationRegistry,
    WorkingPlaceRegistryInterface& workingPlaceRegistry
) :
    size(loader.getMapSize()),
    civilianEntryPoint(CivilianEntryPoint::Create(
        dynamicElements,
        conf.getBuildingConf("mapEntryPoint"),
        loader.getMapEntryPoint(),
        conf.getCharacterConf("immigrant")
    )),
    pathGenerator(*this),
    staticElements(dynamicElements, populationRegistry, workingPlaceRegistry, pathGenerator, *civilianEntryPoint.get()),
    dynamicElements(pathGenerator, staticElements.getBuildingSearchEngine()),
    detailsCache()
{

}



const PathGenerator& Map::getPathGenerator() const
{
    return pathGenerator;
}



MapState Map::getState() const
{
    return MapState(size);
}



QList<BuildingState> Map::getBuildingsState() const
{
    return staticElements.getBuildingsState();
}



QList<NatureElementState> Map::getNatureElementsState() const
{
    return staticElements.getNatureElementsState();
}



QList<CharacterState> Map::getCharactersState() const
{
    return dynamicElements.getCharactersState();
}



void Map::createBuilding(const BuildingInformation& conf, const MapCoordinates& leftCorner, Direction orientation)
{
    MapArea area(leftCorner, conf.getSize(orientation));
    if (!isAreaConstructible(area)) {
        qDebug() << "WARNING: Try to create a building on an occupied area " + area.toString() + ". Skipping the creation.";
        return;
    }

    if (conf.getType() == BuildingInformation::Type::Road) {
        staticElements.generateBuilding(conf, area, orientation);
        for (auto location : area) {
            detailsCache.roadCoordinates.insert(location.getHash());
            detailsCache.nonConstructibleCoordinates.insert(location.getHash());
        }
    }
    else {
        staticElements.generateProcessableBuilding(conf, area, orientation, getBestBuildingEntryPoint(area));
        for (auto location : area) {
            detailsCache.nonTraversableCoordinates.insert(location.getHash());
            detailsCache.nonConstructibleCoordinates.insert(location.getHash());
        }
    }
}



void Map::createNatureElement(const NatureElementInformation& conf, const MapArea& area)
{
    staticElements.generateNatureElement(conf, area);
    for (auto location : area) {
        detailsCache.nonConstructibleCoordinates.insert(location.getHash());
        if (!conf.isTraversable()) {
            detailsCache.nonTraversableCoordinates.insert(location.getHash());
        }
    }
}



bool Map::isLocationValid(const MapCoordinates& coordinates) const
{
    int sum(coordinates.getY() + coordinates.getX());
    int diff(coordinates.getY() - coordinates.getX());

    return (
        diff >= 0 && diff < size.height() &&
        sum >= 0 && sum <= size.width()
    );
}



bool Map::isAreaValid(const MapArea& area) const
{
    if (area.getLeft().getX() == -7 && area.getLeft().getY() == 26) {
        auto top(area.getTop());
    }

    return (
        isLocationValid(area.getLeft()) &&
        isLocationValid(area.getRight()) &&
        isLocationValid(area.getTop()) &&
        isLocationValid(area.getBottom())
    );
}



bool Map::isAreaConstructible(const MapArea& area) const
{
    if (!isAreaValid(area)) {
        return false;
    }

    for (auto location : area) {
        if (detailsCache.nonConstructibleCoordinates.contains(location.getHash())) {
            return false;
        }
    }

    return true;
}



bool Map::isLocationTraversable(const MapCoordinates& location) const
{
    return isLocationValid(location) && !detailsCache.nonTraversableCoordinates.contains(location.getHash());
}



bool Map::hasRoadAtLocation(const MapCoordinates& location) const
{
    return detailsCache.roadCoordinates.contains(location.getHash());
}



bool Map::canConstructRoadAtLocation(const MapCoordinates& location) const
{
    return isLocationValid(location) && (
        !detailsCache.nonConstructibleCoordinates.contains(location.getHash()) ||
        detailsCache.roadCoordinates.contains(location.getHash())
    );
}



void Map::process(const CycleDate& date)
{
    // Note: order is important: dynamic elements, entry points & static elements.
    dynamicElements.process(date);
    civilianEntryPoint->process(date);
    if (date.isBuildingCycle()) {
        staticElements.process(date);
    }
}



MapCoordinates Map::getBestBuildingEntryPoint(const MapArea& area) const
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
