#include "Map.hpp"

#include <QtCore/QDebug>

#include "src/engine/loader/CityLoader.hpp"
#include "src/engine/map/MapArea.hpp"
#include "src/engine/map/MapCoordinates.hpp"
#include "src/engine/map/Tile.hpp"
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
    tiles(),
    civilianEntryPoint(CivilianEntryPoint::Create(
        dynamicElements,
        conf.getBuildingConf("mapEntryPoint"),
        loader.getMapEntryPoint(),
        conf.getCharacterConf("immigrant")
    )),
    pathGenerator(*this),
    staticElements(dynamicElements, populationRegistry, workingPlaceRegistry, pathGenerator, *civilianEntryPoint.get()),
    dynamicElements(pathGenerator, staticElements.getBuildingSearchEngine())
{
    // Create the tiles and their graphics item.
    int line(0);
    int column(0);
    while (line < size.height()) {
        // NOTE: Because we divide by 2 and casting as integer, we deliberately remove floating precision. However, the
        // adjustment needs to be 1 higher when "mapSize.width() - line" become negative. This is because -0.5 is cast
        // to 0 insted of -1.
        int adjust(line > size.width() ? 1 : 2);
        while (column < (size.width() - line + adjust) / 2) {
            auto tile(new Tile(column, line + column));
            tiles.insert(tile->getHash(), tile);

            ++column;
        }
        ++line;
        column = -line / 2;
    }
    for (auto tile : tiles) {
        tile->pickRelatives(tiles);
    }
}



Map::~Map()
{
    qDeleteAll(tiles);
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
    }
    else {
        staticElements.generateProcessableBuilding(conf, area, orientation, getBestBuildingEntryPoint(area));
    }

    for (auto location : area) {
        tiles.value(location.getHash())->registerBuildingConstruction(conf);
    }
}



void Map::createNatureElement(const NatureElementInformation& conf, const MapArea& area)
{
    staticElements.generateNatureElement(conf, area);
    for (auto location : area) {
        tiles.value(location.getHash())->registerNatureElement(conf);
    }
}



bool Map::isLocationValid(const MapCoordinates& coordinates) const
{
    return tiles.contains(coordinates.getHash());
}



bool Map::isAreaValid(const MapArea& area) const
{
    auto size(area.getSize());
    if (size.isSquare() && size.getHeight() == 1) {
        return isLocationValid(area.getLeft());
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
        if (!tiles.value(location.getHash())->isConstructible()) {
            return false;
        }
    }

    return true;
}



bool Map::isLocationTraversable(const MapCoordinates& location) const
{
    if (!tiles.contains(location.getHash())) {
        return false;
    }

    return tiles.value(location.getHash())->isTraversable();
}



bool Map::hasRoadAtLocation(const MapCoordinates& location) const
{
    if (!tiles.contains(location.getHash())) {
        return false;
    }

    return tiles.value(location.getHash())->isRoad();
}



bool Map::canConstructRoadAtLocation(const MapCoordinates& location) const
{
    if (!tiles.contains(location.getHash())) {
        return false;
    }

    auto tile(tiles.value(location.getHash()));

    return tile->isConstructible() || tile->isRoad();
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
    while (!tiles.value(coordinates.getHash())->isRoad()) {
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
